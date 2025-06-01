#include "EntityManager.h"

#include <algorithm>

namespace ECS {

EntityManager::EntityManager()
    : m_archetypes()
    , m_locations()
    , m_free_entities()
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
	Entity e = { 0, 0 };
	if (m_free_entities.empty())
	{
		e.index = static_cast<uint32_t>(m_locations.size());
		m_locations.emplace_back(archetype, allocateChunk(archetype), 0);
	}
	else
	{
		e = m_free_entities.back();
		++e.version;
		m_free_entities.pop_back();
	}

	auto& location  = m_locations.at(e.index);
	location.offset = location.chunk->entity_count++;

	return e;
}

void EntityManager::DeleteEntity(const Entity& entity)
{
	m_free_entities.emplace_back(entity.index);
}

bool EntityManager::IsExistEntity(const Entity& entity) const noexcept
{
	if (m_free_entities.empty())
		return true;

	return std::find(m_free_entities.begin(), m_free_entities.end(), entity) == m_free_entities.end();
}

ComponentDataChunk* EntityManager::allocateChunk(Archetype* archetype)
{
	auto allocate = [this](Archetype* archetype) -> ComponentDataChunk*
	{
		BlockAllocator allocator;
		if (!allocator.Initialize(16, sizeof(ComponentDataChunk) + archetype->GetChunkSize(), 1))
        {
			return nullptr;
        }

        auto chunk = reinterpret_cast<ComponentDataChunk*>(allocator.Allocate());
		if (!chunk)
		{
			return nullptr;
		}
		archetype->m_chunks.emplace_back(chunk);

		chunk->entity_count    = 0;
		chunk->allocator_index = static_cast<uint32_t>(m_chunk_allocators.size());

		m_chunk_allocators.emplace_back(allocator);

        return chunk;
	};

	ComponentDataChunk* ret = nullptr;
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

	return location.chunk->memory() + offset;
}

} // namespace ECS
