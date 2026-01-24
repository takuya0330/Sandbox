#pragma once

#include <cstdint>

namespace STL {

template<typename T>
struct TFNV1;

template<>
struct TFNV1<uint32_t>
{
	static constexpr uint32_t kOffset = 216613626u;
	static constexpr uint32_t kPrime  = 16777619u;

	static constexpr uint32_t Hash(const char* str, const size_t count) noexcept
	{
		return ((count ? Hash(str, count - 1) : kOffset) ^ str[count]) * kPrime;
	}
};

template<>
struct TFNV1<uint64_t>
{
	static constexpr uint64_t kOffset = 14695981039346656037ull;
	static constexpr uint64_t kPrime  = 1099511628211ull;

	static constexpr uint64_t Hash(const char* str, const size_t count) noexcept
	{
		return ((count ? Hash(str, count - 1) : kOffset) ^ str[count]) * kPrime;
	}
};

} // namespace STL
