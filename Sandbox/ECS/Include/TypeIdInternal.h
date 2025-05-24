#pragma once

#include <cstdint>

namespace ECS {
namespace Internal {

// https://stackoverflow.com/a/74453799/475145

template<auto Id>
struct type_counter
{
	using tag = type_counter;

	struct generator
	{
		friend constexpr auto is_defined(tag)
		{
			return true;
		}
	};
	friend constexpr auto is_defined(tag);

	template<typename T = tag, auto = is_defined(T())>
	static constexpr auto exists(auto)
	{
		return true;
	}

	static constexpr auto exists(...)
	{
#pragma warning(disable : 6319)
		return generator(), false;
#pragma warning(default : 6319)
	}
};

template<typename T, auto Id = uint32_t()>
constexpr uint32_t typeid_of_impl() noexcept
{
	if constexpr (Internal::type_counter<Id>::exists(Id))
	{
		return typeid_of_impl<T, Id + 1>();
	}
	return Id;
}

} // namespace Internal
} // namespace ECS
