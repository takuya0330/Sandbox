#include "EntityManager.h"

#include <algorithm>
#include <cassert>

namespace ECS {

EntityManager::EntityManager()
    : m_archetypes()
    , m_locations()
    , m_free_entities()
    , m_chunk_allocator()
{
	// TODO: block_count は外部から設定できるようにする
	m_chunk_allocator.Initialize(16, kMaxChunkSize, 1024);
}

EntityManager::~EntityManager()
{
	m_chunk_allocator.Finalize();
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
	const auto& it = std::find_if(m_archetypes.begin(), m_archetypes.end(), [&sorted_components](const std::unique_ptr<Archetype>& archetype)
	    {
		    return *archetype == sorted_components;
	    });
	if (it != m_archetypes.end())
    {
        return it->get();
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
		e = m_free_entities.front();
		++e.version;
		m_free_entities.pop_front();
	}

	auto& location  = m_locations.at(e.index);
	location.offset = location.chunk->entity_count++;

	return e;
}

void EntityManager::DeleteEntity(const Entity& entity)
{
	m_free_entities.emplace_back(entity);
}

bool EntityManager::IsEntityExists(const Entity& entity) const noexcept
{
	if (m_free_entities.empty())
		return true;

	return std::find(m_free_entities.begin(), m_free_entities.end(), entity) == m_free_entities.end();
}

ComponentDataChunk* EntityManager::allocateChunk(Archetype* archetype)
{
	ComponentDataChunk* chunk = nullptr;
	if (archetype->m_chunks.empty())
	{
		chunk               = m_chunk_allocator.Allocate<ComponentDataChunk>();
		chunk->entity_count = 0;
		archetype->m_chunks.emplace_back(chunk);
	}
	else
	{
		chunk = archetype->m_chunks.back();
		if (chunk->entity_count >= archetype->GetEntityCapacity())
		{
			chunk               = m_chunk_allocator.Allocate<ComponentDataChunk>();
			chunk->entity_count = 0;
			archetype->m_chunks.emplace_back(chunk);
		}
	}
	return chunk;
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
