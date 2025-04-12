#pragma once

#include "ComponentType.h"

#include <vector>

namespace ECS {

class Chunk;

class Archetype
{
public:
	Archetype(std::initializer_list<ComponentType> components);

private:
	std::vector<ComponentType> m_components;
	uint32_t                   m_memory_size;
};

} // namespace ECS
