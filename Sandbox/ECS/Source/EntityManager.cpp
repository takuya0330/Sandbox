#include "EntityManager.h"

#include <algorithm>

namespace ECS {

EntityManager::EntityManager()
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
		if (it->IsEqual(sorted_components))
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
	return {};
}

void EntityManager::DeleteEntity(const Entity& entity)
{
}

} // namespace ECS
