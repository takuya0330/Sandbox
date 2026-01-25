#pragma once

#include <string>
#include <type_traits>

// TODO: char8_t
template<typename T>
concept RequiresCharType =
    std::is_same_v<T, char> ||
    std::is_same_v<T, wchar_t> ||
    std::is_same_v<T, char16_t> ||
    std::is_same_v<T, char32_t>;

template<typename T>
struct TCharTypeOf;

template<RequiresCharType T>
struct TCharTypeOf<T>
{
	using Type = T;
};

template<RequiresCharType T>
struct TCharTypeOf<T*>
{
	using Type = T;
};

template<RequiresCharType T, size_t N>
struct TCharTypeOf<T[N]>
{
	using Type = T;
};

template<RequiresCharType T, class Traits, class Alloc>
struct TCharTypeOf<std::basic_string<T, Traits, Alloc>>
{
	using Type = T;
};

template<RequiresCharType T, class Traits>
struct TCharTypeOf<std::basic_string_view<T, Traits>>
{
	using Type = T;
};

template<RequiresCharType T>
using TCharTypeOf_t = typename TCharTypeOf<std::remove_cvref_t<T>>::Type;
