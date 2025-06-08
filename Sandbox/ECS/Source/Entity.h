#pragma once

#include <cstdint>

namespace ECS {

struct Entity
{
	uint32_t index   = 0xFFFFFFFFu;
	uint32_t version = 0xFFFFFFFFu;

    constexpr bool operator==(const Entity& rhs) const noexcept
    {
		return index == rhs.index && version == rhs.version;
	}
	constexpr bool operator!=(const Entity& rhs) const noexcept
	{
		return !(*this == rhs);
	}
};

} // namespace ECS
