#pragma once

#include "TypeInfo/Include/CharType.h"
#include "TypeInfo/Include/Xorshift.h"

#include <array>

// TODO: char8_t, char16_t, char32_t

constexpr unsigned char HexToVal(char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	if ('a' <= c && c <= 'f')
		return c - 'a' + 10;
	if ('A' <= c && c <= 'F')
		return c - 'A' + 10;
	return 0;
}

template<RequiresCharType T>
constexpr T FromHex1(std::string_view sv, size_t i, bool is_xor = false)
{
	constexpr size_t size = sizeof(T);
	if (sv.size() % size * 2 != 0)
	{
		return {};
	}

	T v = {};
	for (size_t j = 0; j < size; ++j)
	{
		unsigned char c = (HexToVal(sv[j * 2]) << 4) | (HexToVal(sv[j * 2 + 1]));
		if (is_xor)
			c ^= Xorshift<unsigned char>(static_cast<uint32_t>(i * size + j + 1));

		v |= static_cast<T>(c) << (j * 8);
	}
	return v;
}

template<RequiresCharType T, size_t N>
constexpr auto ToHex(const T (&str)[N], bool is_xor = false, bool upper = false)
{
	constexpr std::array<char, 16> kLower = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	constexpr std::array<char, 16> kUpper = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	const auto&      kHex    = upper ? kLower : kUpper;
	constexpr size_t kSize   = sizeof(T);
	constexpr size_t kHexLen = kSize * 2;

	std::array<char, N * kHexLen + 1> ret;
	for (size_t i = 0; i < N; ++i)
	{
		auto v = static_cast<std::make_unsigned_t<T>>(str[i]);
		for (size_t j = 0; j < kSize; ++j)
		{
			auto c = static_cast<unsigned char>(v >> (8 * j));
			if (is_xor)
				c ^= Xorshift<unsigned char>(static_cast<uint32_t>(i * kSize + j + 1));

			ret[i * kHexLen + j * 2]     = kHex[c >> 4];
			ret[i * kHexLen + j * 2 + 1] = kHex[c & 0x0F];
		}
	}
	ret[N * kHexLen] = '\0';
	return ret;
}

template<RequiresCharType T>
std::basic_string<T> FromHex(std::string_view sv, bool is_xor = false)
{
	constexpr size_t kSize    = sizeof(T);
	constexpr size_t kHexLen  = kSize * 2;
	const size_t     kStrSize = sv.size() - 1;
	if (kStrSize % kHexLen != 0)
	{
		return {};
	}

	size_t               num_element = kStrSize / kHexLen;
	std::basic_string<T> ret;
	ret.reserve(num_element);
	for (size_t i = 0; i < num_element; ++i)
	{
		ret.push_back(FromHex1<T>(sv.substr(i * kHexLen, kHexLen), i, is_xor));
	}
	return ret;
}
