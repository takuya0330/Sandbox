#pragma once

#include <memory>

namespace ECS {

class Archetype;

class Chunk
{
public:
	Chunk(Archetype* archetype);

private:
	Archetype*                 m_parent;
	std::unique_ptr<uint8_t[]> m_buffer;
	size_t                     m_capacity;
	size_t                     m_entity_size;
	size_t                     m_entity_count;
};

} // namespace ECS
