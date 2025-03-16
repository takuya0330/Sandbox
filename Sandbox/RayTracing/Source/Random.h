#pragma once

#include <random>

namespace RayTracing {
namespace Util {

template< typename T >
inline T Random(T min, T max)
{
	std::uniform_real_distribution< T > distribution(min, max);
	std::mt19937                        generator { std::random_device {}() };
	return distribution(generator);
}

} // namespace Util
} // namespace RayTracing
