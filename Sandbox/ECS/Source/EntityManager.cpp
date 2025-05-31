#include "EntityManager.h"

#include <algorithm>

namespace ECS {

EntityManager::EntityManager()
    : m_archetypes()
    , m_locations()
    , m_free_indices()
    , m_chunk_allocators()
{
}

EntityManager::~EntityManager()
{
}

Archetype* EntityManager::GetOrCreateArchetype(std::initializer_list<ComponentType> components)
{
	// 昇順にソート
	std::vector sorted_components(components);
	std::sort(sorted_components.begin(), sorted_components.end(), [](const ComponentType& a, const ComponentType& b)
	    {
		    return a.index < b.index;
	    });

	// 作成済みの場合は一致するものを返す
	for (const auto& it : m_archetypes)
	{
		if (*it == sorted_components)
		{
			return it.get();
		}
	}

	// 新規作成
	m_archetypes.emplace_back(std::make_unique<Archetype>(sorted_components));

	return m_archetypes.back().get();
}

Entity EntityManager::CreateEntity(Archetype* archetype)
{
	uint32_t entity_index = 0;
	if (m_free_indices.empty())
	{
		entity_index = static_cast<uint32_t>(m_locations.size());
		m_locations.emplace_back(archetype, allocateChunk(archetype), 0);
	}
	else
	{
		entity_index = m_free_indices.front();
		m_free_indices.pop();
		++m_locations.at(entity_index).version;
	}

	auto& location  = m_locations.at(entity_index);
	location.offset = location.chunk->entity_count++;

	return { entity_index, location.version };
}

void EntityManager::DeleteEntity(const Entity& entity)
{
	m_free_indices.push(entity.index);
}

bool EntityManager::IsExistEntity(const Entity& entity) const noexcept
{
	if (m_free_indices.empty())
		return true;

	for (const auto& it : m_free_indices._Get_container())
	{
		if (it != entity.index)
			continue;

		return false;
	}

	return true;
}

Chunk* EntityManager::allocateChunk(Archetype* archetype)
{
	auto allocate = [this](Archetype* archetype) -> Chunk*
	{
		BlockAllocator allocator;
        if (!allocator.Initialize(16, sizeof(Chunk) + archetype->GetChunkSize(), 1))
        {
			return nullptr;
        }

        auto chunk = reinterpret_cast<Chunk*>(allocator.Allocate());
		if (!chunk)
		{
			return nullptr;
		}
		archetype->m_chunks.emplace_back(chunk);

		chunk->archetype       = archetype;
		chunk->entity_count    = 0;
		chunk->allocator_index = static_cast<uint32_t>(m_chunk_allocators.size());

		m_chunk_allocators.emplace_back(allocator);

        return chunk;
	};

	Chunk* ret = nullptr;
	if (archetype->m_chunks.empty())
    {
		ret = allocate(archetype);
    }
    else
    {
		ret = archetype->m_chunks.back();
        if (ret->entity_count >= archetype->GetEntityCapacity())
        {
			ret = allocate(archetype);
        }
    }
	return ret;
}

const uint8_t* EntityManager::getComponentDataArray(const EntityDataLocation& location, TypeIndex index) const
{
	const auto offset = location.archetype->GetChunkOffset(index);
	if (offset == -1)
	{
		return nullptr;
	}

	return location.chunk->GetMemory() + offset;
}

} // namespace ECS
