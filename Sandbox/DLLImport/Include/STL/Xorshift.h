#pragma once

#include <cstdint>
#include <limits>

namespace STL {

template<typename T>
constexpr T Xorshift(uint32_t seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return static_cast<T>(seed & std::numeric_limits<T>::max());
}

} // namespace STL
