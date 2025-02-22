#pragma once

#include <deque>
#include <memory>
#include <unordered_map>

#include "ComponentDataArray.h"
#include "Entity.h"
#include "TypeInfo.h"

namespace ECS {

class EntityManager
{
public:
	EntityManager()
	    : m_next_entity(0)
	    , m_free_entities()
	    , m_components()
	{
	}

	Entity CreateEntity()
	{
		Entity entity = { 0, 0 };

		if (m_free_entities.empty())
		{
			entity.index = m_next_entity++;
		}
		else
		{
			entity = m_free_entities.front();
			++entity.version;
			m_free_entities.pop_front();
		}

		return entity;
	}

	void DestroyEntity(const Entity& entity)
	{
		m_free_entities.push_back(entity);

		for (auto it = m_components.begin(); it != m_components.end();)
		{
			it->second->Remove(entity);
			if (it->second->Empty())
			{
				it = m_components.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	template< ComponentType T >
	bool AddComponentData(const Entity& entity, T&& value)
	{
		return addComponentData(entity, std::forward< T >(value));
	}

	template< ComponentType... Args >
	bool AddComponents(const Entity& entity)
	{
		return addComponents< Args... >(entity);
	}

	template< ComponentType T >
	void RemoveComponentData(const Entity& entity)
	{
		constexpr auto id = GetTypeID< T >();
		auto           it = m_components.find(id);
		if (it == m_components.end())
		{
			return;
		}

		it->second->Remove(entity);
		if (it->second->Empty())
		{
			m_components.erase(it);
		}
	}

	template< ComponentType T >
	const T* GetComponentData(const Entity& entity) const
	{
		if (!hasComponentDataArray< T >())
		{
			return nullptr;
		}

		return getComponentDataArray< T >()->Get(entity);
	}

	template< ComponentType T >
	T* GetComponentData(const Entity& entity)
	{
		return const_cast< T* >(std::as_const(*this).GetComponentData< T >(entity));
	}

	template< ComponentType T >
	void SetComponentData(const Entity& entity, const T& value)
	{
		if (!hasComponentDataArray< T >())
		{
			return;
		}

		auto arr = getComponentDataArray< T >();
		arr->Set(entity, value);
	}

private:
	template< ComponentType Head, ComponentType... Tail >
	bool addComponentData(const Entity& entity, Head&& head, Tail&&... tail)
	{
		constexpr auto id = GetTypeID< Head >();
		if (m_components.find(id) == m_components.end())
		{
			m_components[id] = std::make_unique< ComponentDataArray< Head > >();
		}

		auto arr = getComponentDataArray< Head >();
		bool ret = arr->Add(entity, std::forward< Head >(head));
		if (!ret)
		{
			return false;
		}

		if constexpr (sizeof...(Tail) > 0)
		{
			ret = addComponentData(entity, std::forward< Tail >(tail)...);
		}

		return ret;
	}

	template< ComponentType Head, ComponentType... Tail >
	bool addComponents(const Entity& entity)
	{
		constexpr auto id = GetTypeID< Head >();
		if (m_components.find(id) == m_components.end())
		{
			m_components[id] = std::make_unique< ComponentDataArray< Head > >();
		}

		auto arr = getComponentDataArray< Head >();
		bool ret = arr->Add(entity, Head {});
		if (!ret)
		{
			return false;
		}

		if constexpr (sizeof...(Tail) > 0)
		{
			ret = addComponents< Tail... >(entity);
		}

		return ret;
	}

	template< ComponentType T >
	bool hasComponentDataArray() const noexcept
	{
		return m_components.find(GetTypeID< T >()) != m_components.end();
	}

	template< ComponentType T >
	ComponentDataArray< T >* getComponentDataArray() const
	{
		return static_cast< ComponentDataArray< T >* >(m_components.at(GetTypeID< T >()).get());
	}

private:
	EntityIndexType                                                      m_next_entity;
	std::deque< Entity >                                                 m_free_entities;
	std::unordered_map< TypeID, std::unique_ptr< IComponentDataArray > > m_components;
};

} // namespace ECS
