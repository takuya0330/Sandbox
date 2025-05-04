#include "Chunk.h"

#include "Archetype.h"

namespace ECS {

Chunk::Chunk(Archetype* archetype)
    : m_parent(archetype)
    , m_memory(new uint8_t[archetype->GetMemorySize()])
    , m_entity_count(0)
{
}

bool Chunk::IsFull() const noexcept
{
	return m_entity_count >= m_parent->GetMaxEntityCount();
}

uint32_t Chunk::IncEntityCount() noexcept
{
	return m_entity_count++;
}

const uint8_t* Chunk::GetDataArray(TypeId id) const
{
	const auto offset = m_parent->GetMemoryOffset(id);
	if (offset == -1)
		return nullptr;

    return m_memory.get() + offset;
}

} // namespace ECS
