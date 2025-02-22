#pragma once

#define ECS_TYPEID_STATIC    0
#define ECS_TYPEID_CONSTEXPR 0 // TODO: stateful metaprogramming.
#define ECS_TYPEID_HASH_FNV  1

#if ECS_TYPEID_STATIC
#include <atomic>
#elif ECS_TYPEID_CONSTEXPR
#elif ECS_TYPEID_HASH_FNV
#endif

#include <cstdint>
#include <string_view>

namespace ECS {

using TypeID = uint32_t;

namespace Internal {

template< class T >
constexpr std::string_view MakeTypeName() noexcept
{
	std::string_view func  = __FUNCSIG__; // TODO: コンパイラ依存
	auto             begin = func.find_last_of('<') + 1;
	return func.substr(begin, func.find_last_of('>') - begin);
}

#if ECS_TYPEID_STATIC

static TypeID MakeTypeID() noexcept
{
	static std::atomic< TypeID > id = 0;
	return id++;
}

} // namespace Internal

template< class T >
static const TypeID GetTypeID() noexcept
{
	static const auto id = Internal::MakeTypeID();
	return id;
}

#elif ECS_TYPEID_CONSTEXPR

#elif ECS_TYPEID_HASH_FNV

template< class T >
struct FNV1;

template<>
struct FNV1< uint32_t >
{
	static constexpr uint32_t kOffset = 216613626u;
	static constexpr uint32_t kPrime  = 16777619u;

	static constexpr uint32_t Hash(const char* str, const size_t count) noexcept
	{
		return ((count ? Hash(str, count - 1) : kOffset) ^ str[count]) * kPrime;
	}
};

template<>
struct FNV1< uint64_t >
{
	static constexpr uint64_t kOffset = 14695981039346656037ull;
	static constexpr uint64_t kPrime  = 1099511628211ull;

	static constexpr uint64_t Hash(const char* str, const size_t count) noexcept
	{
		return ((count ? Hash(str, count - 1) : kOffset) ^ str[count]) * kPrime;
	}
};

#endif

} // namespace Internal

template< class T >
constexpr std::string_view GetTypeName() noexcept
{
	return Internal::MakeTypeName< T >();
}

#if ECS_TYPEID_STATIC

template< class T >
static const TypeID GetTypeID() noexcept
{
	static const auto id = Internal::MakeTypeID();
	return id;
}

#else

template< class T >
constexpr TypeID GetTypeID() noexcept
{
	constexpr auto name = Internal::MakeTypeName< T >();
	return Internal::FNV1< TypeID >::Hash(name.data(), name.size());
}

#endif

} // namespace ECS
