#pragma once

#include "TypeId.h"

#include <memory>

namespace ECS {

class Archetype;

class Chunk
{
public:
	Chunk(Archetype* archetype);

	bool IsFull() const noexcept;

	uint32_t IncEntityCount() noexcept;

	const uint8_t* GetDataArray(TypeId id) const;

	uint8_t* GetDataArray(TypeId id)
	{
		return const_cast<uint8_t*>(std::as_const(*this).GetDataArray(id));
	}

private:
	const Archetype*           m_parent;
	std::unique_ptr<uint8_t[]> m_memory;
	uint32_t                   m_entity_count;
};

} // namespace ECS
