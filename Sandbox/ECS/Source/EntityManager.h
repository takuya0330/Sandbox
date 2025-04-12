#pragma once

#include "Archetype.h"
#include "Entity.h"

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
	struct EntityData
	{
		Archetype* archetype;
		Chunk*     chunk;
		uint32_t   chunk_index;
		uint32_t   version;
	};

private:
};

} // namespace ECS
