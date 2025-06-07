#pragma once

#include "Entity.h"

#include <deque>

namespace ECS {

class EntityManager
{
public:
	EntityManager();

	~EntityManager();

	std::weak_ptr<EntityArchetype> GetOrCreateArchetype(std::initializer_list<ComponentType> components);

	template<ComponentDataType... Ts>
	std::weak_ptr<EntityArchetype> GetOrCreateArchetype()
	{
		return GetOrCreateArchetype({ (GetComponentType<Ts>())... });
	}

	Entity CreateEntity(std::weak_ptr<EntityArchetype> archetype);

	Entity CreateEntity(std::initializer_list<ComponentType> components)
	{
		return CreateEntity(GetOrCreateArchetype(std::move(components)));
	}

	template<ComponentDataType... Ts>
	Entity CreateEntity()
	{
		return CreateEntity({ (GetComponentType<Ts>())... });
	}

	void DeleteEntity(Entity entity);

	bool IsEntityExists(Entity entity) const noexcept;

private:
	struct EntityDataLocation
	{
		EntityArchetype*    archetype;
		ComponentDataChunk* chunk;
		uint32_t            chunk_offset;
	};

private:

private:
	std::list<std::shared_ptr<EntityArchetype>> m_archetypes;
	std::vector<EntityDataLocation>             m_locations;
	std::deque<Entity>                          m_free_entities;
};

} // namespace ECS
