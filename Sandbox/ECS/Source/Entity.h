#pragma once

#include "ComponentData.h"

#include <list>
#include <unordered_map>
#include <vector>

namespace ECS {

struct EntityArchetype
{
	std::vector<ComponentType>            components;
	size_t                                entity_capacity;
	std::list<ComponentDataChunk>         chunks;
	std::unordered_map<TypeIndex, size_t> chunk_offsets;
	size_t                                chunk_size;
};

using Entity        = uint64_t;
using EntityIndex   = uint32_t;
using EntityVersion = uint32_t;

constexpr Entity kInvalidEntity = 0xFFFFFFFFFFFFFFFFull;

EntityIndex   GetEntityIndex(Entity entity);
EntityVersion GetEntityVersion(Entity entity);

} // namespace ECS
