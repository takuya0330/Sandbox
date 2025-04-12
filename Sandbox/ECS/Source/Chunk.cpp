#include "Chunk.h"

#include "Archetype.h"

namespace ECS {

Chunk::Chunk(Archetype* archetype)
    : m_parent(archetype)
    , m_buffer(new uint8_t[archetype->GetMemorySize()])
    , m_entity_count(0)
{
}

const uint8_t* Chunk::GetDataArray(TypeId id) const
{
	const auto offset = m_parent->GetOffset(id);
	if (offset == -1)
		return nullptr;

    return m_buffer.get() + offset;
}

const uint8_t* Chunk::GetData(TypeId id, uint32_t index) const
{
	return GetDataArray(id) + index;
}

} // namespace ECS
