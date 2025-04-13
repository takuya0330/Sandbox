#pragma once

#include "Archetype.h"
#include "Entity.h"

#include <memory>

namespace ECS {

class EntityManager
{
public:
	EntityManager();

	Archetype* GetOrCreateArchetype(std::initializer_list<ComponentType> components);

	template<ComponentDataType... Ts>
	Archetype* GetOrCreateArchetype()
	{
		return GetOrCreateArchetype({ (GetComponentType<Ts>())... });
	}

	Entity CreateEntity(Archetype* archetype);

	Entity CreateEntity(std::initializer_list<ComponentType> components)
	{
		return CreateEntity(GetOrCreateArchetype(components));
	}

	template<ComponentDataType... Ts>
	Entity CreateEntity()
	{
		return CreateEntity({ (GetComponentType<Ts>())... });
	}

	void DeleteEntity(const Entity& entity);

private:
	std::vector<std::unique_ptr<Archetype>> m_archetypes;
};

} // namespace ECS
