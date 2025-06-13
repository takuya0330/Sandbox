#pragma once

#include "Component.h"

#include <list>
#include <vector>

namespace ECS {

class EntityManager;

struct EntityArchetype;

struct EntityQuery
{
	std::vector<ComponentType> all;
	std::vector<ComponentType> any;
	std::vector<ComponentType> none;
};

template<ComponentDataConstraints T>
class ComponentDataArray
{
public:
	ComponentDataArray()
	    : ComponentDataArray(nullptr, 0)
	{
	}

	ComponentDataArray(T* begin, size_t size)
	    : m_begin(begin)
	    , m_size(size)
	{
	}

private:
	T*     m_begin;
	size_t m_size;
};

class ComponentDataGroup
{
public:
	ComponentDataGroup(EntityManager& entity_manager);

    ComponentDataGroup& Include(std::initializer_list<ComponentType> components);

    ComponentDataGroup& Exclude(std::initializer_list<ComponentType> components);

	void Build();

    size_t GetSize() const;

public:
	template<ComponentDataConstraints... Ts>
	ComponentDataGroup& Include()
	{
		return Include({ GetComponentType<Ts>()... });
	}

	template<ComponentDataConstraints... Ts>
	ComponentDataGroup& Exclude()
	{
		return Exclude({ GetComponentType<Ts>()... });
	}

	template<ComponentDataConstraints T>
	ComponentDataArray<T> GetComponentDataArray()
	{
		return ComponentDataArray<T>();
	}

private:
	EntityManager&              m_entity_manager;
	EntityQuery                 m_query;
	std::list<EntityArchetype*> m_archetypes;
};

} // namespace ECS
