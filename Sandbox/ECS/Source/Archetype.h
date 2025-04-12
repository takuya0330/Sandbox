#pragma once

#include "ComponentType.h"

#include <unordered_map>
#include <vector>

namespace ECS {

static constexpr uint32_t kMaxChunkSize = 16 * 1024;

class Chunk;

class Archetype
{
public:
	Archetype(std::initializer_list<ComponentType> components);

	const size_t GetOffset(TypeId id) const;

	template<ComponentDataType T>
	const size_t GetOffset() const
	{
		return GetOffset(GetComponentTypeId<T>());
	}

    const size_t GetEntityCapacity() const noexcept
    {
		return m_entity_capacity;
    }

    const size_t GetMemorySize() const noexcept
	{
		return m_memory_size;
	}

private:
	std::vector<ComponentType>         m_components;
	std::unordered_map<size_t, size_t> m_offset_map;
	size_t                             m_total_size;
	size_t                             m_entity_capacity;
	size_t                             m_memory_size;
};

} // namespace ECS
