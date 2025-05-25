#pragma once

#include "Archetype.h"

namespace ECS {

struct Entity
{
	uint32_t index;
	uint32_t version;

	inline constexpr bool operator==(const Entity& e) const noexcept
	{
		return index == e.index && version == e.version;
	}

	inline constexpr bool operator!=(const Entity& e) const noexcept
	{
		return !(*this == e);
	}
};

} // namespace ECS
