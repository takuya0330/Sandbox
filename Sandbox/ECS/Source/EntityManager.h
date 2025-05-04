#pragma once

#include "Archetype.h"
#include "Chunk.h"
#include "Entity.h"

#include <memory>
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
		const auto& location = m_locations.at(0); // 先頭から取得
		return location.chunk->GetData<T>(location.offset);
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
		return location.chunk->GetData<T>(location.offset);
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
	std::vector<std::unique_ptr<Archetype>> m_archetypes;
	std::vector<EntityDataLocation>         m_locations;
	std::queue<uint32_t>                    m_free_indices;
};

} // namespace ECS
