#include "EntityManager.h"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace ECS {
namespace Internal {

void MakeSortedComponentTypes(std::vector<ComponentType>& sorted_components, std::initializer_list<ComponentType> unsorted_components)
{
	sorted_components = std::move(unsorted_components);
	std::sort(
	    sorted_components.begin(),
	    sorted_components.end(),
	    [](const ComponentType& a, const ComponentType& b)
	    {
		    return a.index < b.index;
	    });
}

} // namespace Internal
namespace {

constexpr size_t alignup(size_t value, size_t align)
{
	return (value + (align - 1)) & ~(align - 1);
}

} // namespace

EntityManager::EntityManager()
    : m_archetypes()
    , m_locations()
    , m_free_entities()
{
}

EntityManager::~EntityManager()
{
}

EntityArchetype* EntityManager::GetOrCreateArchetype(std::initializer_list<ComponentType> components)
{
	// 昇順にソート
	std::vector<ComponentType> sorted_components;
	Internal::MakeSortedComponentTypes(sorted_components, components);

	// 一致するアーキタイプが存在するか確認
	EntityArchetype* archetype = nullptr;
	if (getArchetype(&archetype, sorted_components))
	{
		return archetype;
	}

	// 存在しない場合は新しいアーキタイプを作成
	m_archetypes.emplace_back();
	archetype = &m_archetypes.back();
	{
		// コンポーネントサイズの合計
		size_t total_size = std::accumulate(
		    sorted_components.begin(),
		    sorted_components.end(),
		    0ull,
		    [](size_t i, const ComponentType& c)
		    {
			    return i + alignup(c.size, kCacheLineSize);
		    });

		// チャンク内のエンティティの最大数
		size_t entity_capacity = kMaxChunkSize / total_size;

		// チャンク内のメモリオフセット位置とメモリ最大値を計算
		size_t                                chunk_size = 0;
		std::unordered_map<TypeIndex, size_t> chunk_offsets;
		for (const auto& it : sorted_components)
		{
			chunk_size = alignup(chunk_size, kCacheLineSize);
			chunk_offsets.try_emplace(it.index, chunk_size);
			chunk_size += it.size * entity_capacity;
		}
		assert(chunk_size <= kMaxChunkSize);

		// 初期化
		archetype->components      = std::move(sorted_components);
		archetype->entity_capacity = kMaxChunkSize / total_size;
		archetype->chunk_size      = chunk_size;
		archetype->chunk_offsets   = std::move(chunk_offsets);

		// チャンクの作成
		createChunk(archetype);
	}

	return archetype;
}

bool EntityManager::FindMatchingArchetypes(std::list<EntityArchetype*>& outs, const EntityQuery& query)
{
	// 完全一致するアーキタイプを検索
	if (!query.all.empty())
	{
		for (auto& archetype : m_archetypes)
		{
			if (archetype.components == query.all)
			{
				outs.emplace_back(&archetype);
			}
		}
	}

	// いずれかが一致するアーキタイプを検索
	if (!query.any.empty())
	{
		for (auto& component : query.any)
		{
			for (auto& archetype : m_archetypes)
			{
				// コンポーネントがアーキタイプに含まれているか確認
				if (std::find(archetype.components.begin(), archetype.components.end(), component) == archetype.components.end())
					continue;

				// 登録済みか確認
				if (std::find(outs.begin(), outs.end(), &archetype) != outs.end())
					continue;

				outs.emplace_back(&archetype);
			}
		}
	}

	// 除外コンポーネントを持つアーキタイプを除外
	if (!query.none.empty())
	{
		for (auto& component : query.none)
		{
			for (auto it = outs.begin(); it != outs.end();)
			{
				auto& archetype = *it;
				if (std::find(archetype->components.begin(), archetype->components.end(), component) != archetype->components.end())
				{
					it = outs.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}

	return !outs.empty();
}

Entity EntityManager::CreateEntity(EntityArchetype* archetype)
{
	Entity new_entity;

	// nullptr の場合は無効なエンティティを返す
	if (!archetype)
	{
		return new_entity;
	}

	if (m_free_entities.empty())
	{
		new_entity.index   = static_cast<uint32_t>(m_locations.size());
		new_entity.version = 0;
		m_locations.emplace_back();
	}
	else
	{
		Entity old_entity  = m_free_entities.front();
		new_entity.index   = old_entity.index;
		new_entity.version = old_entity.version + 1;
		m_free_entities.pop_front();
	}

	// チャンクが存在するか確認
	if (archetype->chunks.empty())
	{
		// チャンクが存在しない場合は新しいチャンクを作成
		createChunk(archetype);
	}

	// チャンクの容量を確認
	auto chunk = &archetype->chunks.back();
	if (chunk->entity_count >= archetype->entity_capacity)
	{
		// チャンクがいっぱいなら新しいチャンクを作成
		chunk = createChunk(archetype);
	}

	auto& location        = m_locations.at(new_entity.index);
	location.archetype    = archetype;
	location.chunk        = chunk;
	location.chunk_offset = chunk->entity_count++;

	return new_entity;
}

void EntityManager::DeleteEntity(const Entity& entity)
{
	if (!IsEntityExists(entity))
	{
		// 既に削除済み
		return;
	}
	m_free_entities.emplace_back(entity);

	auto& location = m_locations.at(entity.index);
	if (--location.chunk->entity_count == 0)
	{
		auto it = std::find_if(
		    location.archetype->chunks.begin(),
		    location.archetype->chunks.end(),
		    [&location](const ComponentDataChunk& chunk)
		    {
			    return &chunk == location.chunk;
		    });
		if (it != location.archetype->chunks.end())
		{
			location.chunk        = nullptr;
			location.chunk_offset = -1;
			location.archetype->chunks.erase(it);
		}

#if 0 // Unity の実装では World が破棄されるまでアーキタイプは削除されない
      // チャンクが空ならアーキタイプを削除
		if (location.archetype->chunks.empty())
		{
			auto it = std::find_if(
			    m_archetypes.begin(),
			    m_archetypes.end(),
			    [&location](const std::shared_ptr<EntityArchetype>& archetype)
			    {
				    return archetype.get() == location.archetype;
			    });
			if (it != m_archetypes.end())
			{
				location.archetype = nullptr;
				m_archetypes.erase(it);
			}
		}
#endif
	}
}

bool EntityManager::IsEntityExists(const Entity& entity) const noexcept
{
	if (m_free_entities.empty())
	{
		return true;
	}

	return std::find(m_free_entities.begin(), m_free_entities.end(), entity) == m_free_entities.end();
}

bool EntityManager::AddComponentData(const Entity& entity, const ComponentType& component)
{
	return true;
}

bool EntityManager::RemoveComponentData(const Entity& entity, const ComponentType& component)
{
    return true;
}

bool EntityManager::getArchetype(EntityArchetype** archetype, const std::vector<ComponentType>& components)
{
	const auto& it = std::find_if(
	    m_archetypes.begin(),
	    m_archetypes.end(),
	    [&components](const EntityArchetype& archetype)
	    {
		    return archetype.components == components;
	    });
	*archetype = (it != m_archetypes.end()) ? &(*it) : nullptr;
	return *archetype != nullptr;
}

ComponentDataChunk* EntityManager::createChunk(EntityArchetype* archetype)
{
	archetype->chunks.emplace_back();
	auto chunk          = &archetype->chunks.back();
	chunk->buffer       = std::make_unique<uint8_t[]>(archetype->chunk_size);
	chunk->entity_count = 0;

	return chunk;
}

} // namespace ECS
