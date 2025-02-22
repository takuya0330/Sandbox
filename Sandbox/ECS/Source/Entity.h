#pragma once

#include <cstdint>
#include <limits>

namespace ECS {

using EntityIndexType   = uint32_t;
using EntityVersionType = uint32_t;

constexpr auto kMaxEntitiyIndex   = std::numeric_limits< EntityIndexType >::max();
constexpr auto kMaxEntitiyVersion = std::numeric_limits< EntityVersionType >::max();

struct Entity
{
	EntityIndexType   index   = kMaxEntitiyIndex;
	EntityVersionType version = kMaxEntitiyVersion;
};

} // namespace ECS
