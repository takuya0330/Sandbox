#pragma once

#include "ComponentData.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace ECS {

class Archetype
{
public:
	Archetype(const std::vector<ComponentType>& components);

	bool operator==(const Archetype& ar) const noexcept
	{
		return isEqual(ar.m_components);
	}

	bool operator!=(const Archetype& ar) const noexcept
	{
		return !(*this == ar);
	}

	bool operator==(const std::vector<ComponentType>& components) const noexcept
	{
		return isEqual(components);
	}

	bool operator!=(const std::vector<ComponentType>& components) const noexcept
	{
		return !(*this == components);
	}

	const size_t GetChunkOffset(TypeId id) const;

	const size_t GetChunkSize() const noexcept
	{
		return m_memory_size;
	}

	const size_t GetEntityCapacity() const noexcept
	{
		return m_entity_capacity;
	}

private:
	bool isEqual(const std::vector<ComponentType>& components) const noexcept;

private:
	std::vector<ComponentType>         m_components;
	std::unordered_map<TypeId, size_t> m_chunk_offsets;
	size_t                             m_total_size;
	size_t                             m_entity_capacity;
	size_t                             m_memory_size;
};

} // namespace ECS
