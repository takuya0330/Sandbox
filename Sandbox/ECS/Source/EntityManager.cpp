#include "EntityManager.h"

#include <algorithm>

namespace ECS {

EntityManager::EntityManager()
    : m_archetypes()
    , m_locations()
    , m_free_indices()
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
		    return a.id < b.id;
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
		m_locations.emplace_back(nullptr, nullptr, 0);
	}
	else
	{
		entity_index = m_free_indices.front();
		m_free_indices.pop();
		++m_locations.at(entity_index).version;
	}

	auto& location     = m_locations.at(entity_index);
	location.archetype = archetype;
	location.chunk     = archetype->GetOrCreateChunk();
	location.offset    = location.chunk->AddEntityCount();

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

} // namespace ECS
