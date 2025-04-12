#include "Chunk.h"

#include "Archetype.h"

namespace ECS {

static constexpr uint32_t kMaxChunkSize = 16 * 1024;

Chunk::Chunk(Archetype* archetype)
    : m_parent(archetype)
    , m_buffer(std::make_unique<uint8_t[]>(kMaxChunkSize))
    , m_capacity(kMaxChunkSize)
    , m_entity_size(0)
    , m_entity_count(0)
{
}

} // namespace ECS
