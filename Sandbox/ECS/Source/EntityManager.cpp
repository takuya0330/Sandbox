#include "EntityManager.h"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace ECS {
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

std::weak_ptr<EntityArchetype> EntityManager::GetOrCreateArchetype(std::initializer_list<ComponentType> components)
{
	// 昇順にソート
	std::vector<ComponentType> sorted_components = std::move(components);
	std::sort(
	    sorted_components.begin(),
	    sorted_components.end(),
	    [](const ComponentType& a, const ComponentType& b)
	    {
		    return a.id < b.id;
	    });

	// 一致するアーキタイプが存在するか確認
	auto it = std::find_if(
	    m_archetypes.begin(),
	    m_archetypes.end(),
	    [&sorted_components](const std::shared_ptr<EntityArchetype>& archetype)
	    {
		    return archetype->components == sorted_components;
	    });
	if (it != m_archetypes.end())
	{
		// チャンクの容量を確認
		// ここで見つかったアーキタイプはチャンクを1つ以上所持している前提
		auto& chunk = (*it)->chunks.back();
		if (chunk.entity_count >= (*it)->entity_capacity)
		{
			// チャンクがいっぱいなら新しいチャンクを作成
			(*it)->chunks.emplace_back();
			auto& new_chunk        = (*it)->chunks.back();
			new_chunk.buffer       = std::make_unique<uint8_t[]>((*it)->chunk_size);
			new_chunk.entity_count = 0;
		}
		return *it;
	}

	// 存在しない場合は新しいアーキタイプを作成
	m_archetypes.emplace_back(std::make_shared<EntityArchetype>());
	auto& archetype = m_archetypes.back();
	{
		// コンポーネントサイズの合計
		size_t total_size = std::accumulate(
		    sorted_components.begin(),
		    sorted_components.end(),
		    0ull,
		    [](size_t i, const ComponentType& c)
		    {
			    return i + alignup(c.size, c.alignment);
		    });

		// チャンク内のエンティティの最大数
		size_t entity_capacity = kMaxChunkSize / total_size;

		// チャンク内のメモリオフセット位置とメモリ最大値を計算
		size_t                               chunk_size = 0;
		std::unordered_map<uint64_t, size_t> chunk_offsets;
		for (const auto& it : sorted_components)
		{
			chunk_size           = alignup(chunk_size, it.alignment);
			chunk_offsets[it.id] = chunk_size;
			chunk_size += it.size * entity_capacity;
		}
		assert(chunk_size <= kMaxChunkSize);

		// 初期化
		archetype->components      = std::move(sorted_components);
		archetype->entity_capacity = kMaxChunkSize / total_size;
		archetype->chunk_size      = chunk_size;
		archetype->chunk_offsets   = std::move(chunk_offsets);

		// チャンクの作成
		archetype->chunks.emplace_back();
		auto& chunk        = archetype->chunks.back();
		chunk.buffer       = std::make_unique<uint8_t[]>(chunk_size);
		chunk.entity_count = 0;
	}

	return archetype;
}

Entity EntityManager::CreateEntity(std::weak_ptr<EntityArchetype> archetype)
{
	Entity new_entity;

	auto locked_archetype = archetype.lock();
	if (locked_archetype == nullptr)
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
		auto old_entity    = m_free_entities.front();
		new_entity.index   = old_entity.index;
		new_entity.version = old_entity.version + 1;
		m_free_entities.pop_front();
	}

	auto& location        = m_locations.at(new_entity.index);
	location.archetype    = locked_archetype.get();
	location.chunk        = &locked_archetype->chunks.back();
	location.chunk_offset = location.chunk->entity_count++;

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

} // namespace ECS
