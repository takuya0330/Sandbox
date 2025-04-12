#include "EntityManager.h"

namespace ECS {

EntityManager::EntityManager()
{
}

Archetype* EntityManager::GetOrCreateArchetype(std::initializer_list<ComponentType> components)
{
	return nullptr;
}

Entity EntityManager::CreateEntity(Archetype* archetype)
{
	return {};
}

void EntityManager::DeleteEntity(const Entity& entity)
{
}

} // namespace ECS
