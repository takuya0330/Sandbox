#pragma once

#include <memory>

namespace ECS {

class Archetype;

struct Chunk
{
	const Archetype* archetype;
	uint32_t         entity_count;
	uint32_t         allocator_index;

    const uint8_t* GetMemory() const
	{
		return (uint8_t*)this + sizeof(Chunk);
	}

	uint8_t* GetMemory()
	{
		return const_cast<uint8_t*>(std::as_const(*this).GetMemory());
	}
};

} // namespace ECS
