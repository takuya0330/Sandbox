#pragma once

#include "Component.h"
#include "Entity.h"

#include <list>
#include <memory>
#include <unordered_map>
#include <vector>
#include <deque>

namespace ECS {

constexpr size_t kMaxChunkSize = 16 * 1024;

struct ComponentDataChunk
{
	std::unique_ptr<uint8_t[]> buffer;
	uint32_t                   entity_count;
};

struct EntityArchetype
{
	std::vector<ComponentType>           components;
	size_t                               entity_capacity;
	std::list<ComponentDataChunk>        chunks;
	std::unordered_map<uint64_t, size_t> chunk_offsets;
	size_t                               chunk_size;
};

struct EntityDataLocation
{
	EntityArchetype*    archetype;
	ComponentDataChunk* chunk;
	uint32_t            chunk_offset;
};

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

	void DeleteEntity(const Entity& entity);

	bool IsEntityExists(const Entity& entity) const noexcept;

private:
	std::list<std::shared_ptr<EntityArchetype>> m_archetypes;
	std::vector<EntityDataLocation>             m_locations;
	std::deque<Entity>                          m_free_entities;
};

} // namespace ECS
