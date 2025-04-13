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

	const size_t GetMemoryOffset(TypeId id) const;

	template<ComponentDataType T>
	const size_t GetMemoryOffset() const
	{
		return GetMemoryOffset(GetComponentTypeId<T>());
	}

	const size_t GetMemorySize() const noexcept
	{
		return m_memory_size;
	}

	const size_t GetMaxEntityCount() const noexcept
	{
		return m_max_entity_count;
	}

private:
	std::vector<ComponentType>         m_components;
	std::unordered_map<size_t, size_t> m_offset_map;
	size_t                             m_total_size;
	size_t                             m_max_entity_count;
	size_t                             m_memory_size;
};

} // namespace ECS
