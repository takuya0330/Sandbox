#pragma once

#include "ComponentGroup.h"
#include "Entity.h"

#include <deque>
#include <list>
#include <memory>
#include <unordered_map>

namespace ECS {
namespace Internal {

void MakeSortedComponentTypes(std::vector<ComponentType>& sorted_components, std::initializer_list<ComponentType> unsorted_components);

} // namespace Internal

constexpr size_t kMaxChunkSize  = 16 * 1024;
constexpr size_t kCacheLineSize = 16;

struct ComponentDataChunk
{
	std::unique_ptr<uint8_t[]> buffer;
	uint32_t                   entity_count;
};

struct EntityArchetype
{
	std::vector<ComponentType>            components;
	size_t                                entity_capacity;
	std::list<ComponentDataChunk>         chunks;
	std::unordered_map<TypeIndex, size_t> chunk_offsets;
	size_t                                chunk_size;
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

	EntityArchetype* GetOrCreateArchetype(std::initializer_list<ComponentType> components);

	template<ComponentDataConstraints... Ts>
	EntityArchetype* GetOrCreateArchetype()
	{
		return GetOrCreateArchetype({ GetComponentType<Ts>()... });
	}

	bool FindMatchingArchetypes(std::list<EntityArchetype*>& outs, const EntityQuery& query);

	Entity CreateEntity(EntityArchetype* archetype);

	Entity CreateEntity(std::initializer_list<ComponentType> components)
	{
		return CreateEntity(GetOrCreateArchetype(std::move(components)));
	}

	template<ComponentDataConstraints... Ts>
	Entity CreateEntity()
	{
		return CreateEntity({ GetComponentType<Ts>()... });
	}

	void DeleteEntity(const Entity& entity);

	bool IsEntityExists(const Entity& entity) const noexcept;

private:
	bool getArchetype(EntityArchetype** archetype, const std::vector<ComponentType>& components);

	ComponentDataChunk* createChunk(EntityArchetype* archetype);

private:
	std::list<EntityArchetype>      m_archetypes;
	std::vector<EntityDataLocation> m_locations;
	std::deque<Entity>              m_free_entities;
};

} // namespace ECS
