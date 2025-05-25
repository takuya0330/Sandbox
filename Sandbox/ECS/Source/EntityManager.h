#pragma once

#include "Archetype.h"
#include "BlockAllocator.h"
#include "Chunk.h"
#include "Entity.h"

#include <queue>

namespace ECS {

class EntityManager
{
public:
	EntityManager();

	~EntityManager();

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

	bool IsExistEntity(const Entity& entity) const noexcept;

	template<ComponentDataType T>
	const T* GetComponentDataArray() const
	{
		const auto& location = m_locations.at(0);
		return reinterpret_cast<const T*>(getComponentDataArray(location, TypeIdOf<T>()));
	}

	template<ComponentDataType T>
	T* GetComponentDataArray()
	{
		return const_cast<T*>(std::as_const(*this).GetComponentDataArray<T>());
	}

	template<ComponentDataType T>
	const T* GetComponentData(const Entity& entity) const
	{
		const auto& location = m_locations.at(entity.index);
		if (entity.index >= location.chunk->entity_count)
			return nullptr;

        const T* arr = reinterpret_cast<const T*>(getComponentDataArray(location, TypeIdOf<T>()));
		if (!arr)
			return nullptr;

        return arr + location.offset;
	}

	template<ComponentDataType T>
	T* GetComponentData(const Entity& entity)
	{
		return const_cast<T*>(std::as_const(*this).GetComponentData<T>(entity));
	}

private:
	struct EntityDataLocation
	{
		Archetype* archetype;
		Chunk*     chunk;
		uint32_t   offset;
		uint32_t   version;
	};

private:
	Chunk* getOrAllocateChunk(const Archetype* archetype);

	const uint8_t* getComponentDataArray(const EntityDataLocation& location, TypeId id) const;

	uint8_t* getComponentDataArray(const EntityDataLocation& location, TypeId id)
	{
		return const_cast<uint8_t*>(std::as_const(*this).getComponentDataArray(location, id));
	}

private:
	std::vector<std::unique_ptr<Archetype>>              m_archetypes;
	std::vector<EntityDataLocation>                      m_locations;
	std::queue<uint32_t>                                 m_free_indices;
	std::unordered_map<const Archetype*, BlockAllocator> m_chunk_allocators;
	std::unordered_map<const Archetype*, Chunk*>         m_chunks;
};

} // namespace ECS
