#pragma once

#include "ComponentType.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace ECS {

static constexpr uint32_t kMaxChunkSize = 16 * 1024;

class Chunk;

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

	Chunk* GetOrCreateChunk();

	const size_t GetMemoryOffset(TypeId id) const;

	const size_t GetMemorySize() const noexcept
	{
		return m_memory_size;
	}

	const size_t GetMaxEntityCount() const noexcept
	{
		return m_max_entity_count;
	}

private:
	bool isEqual(const std::vector<ComponentType>& components) const noexcept;

private:
	std::vector<ComponentType>           m_components;
	std::unordered_map<uint32_t, size_t> m_offset_map;
	size_t                               m_total_size;
	size_t                               m_max_entity_count;
	size_t                               m_memory_size;
	std::vector<std::unique_ptr<Chunk>>  m_chunks;
};

} // namespace ECS
