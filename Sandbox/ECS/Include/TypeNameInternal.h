#pragma once

#include <string_view>

namespace ECS {
namespace Internal {

template<typename T>
using has_name_of_t = decltype(_name_of((T*)nullptr));

template<typename T>
constexpr bool has_name_of_v = requires { has_name_of_t<T>(); };

template<typename T>
constexpr std::string_view name_of_impl()
{
#if _DEBUG
	static_assert(has_name_of_v<T>,  "_name_of(T*) function not found.");
#endif
	if constexpr (has_name_of_v<T>)
	{
		return _name_of((T*)nullptr);
	}
	return "WARNING: Unknown";
}

} // namespace Internal
} // namespace ECS
