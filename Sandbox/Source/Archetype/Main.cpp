#include <iostream>
#include <cassert>
#include <tuple>

template<typename TypeList, size_t Index>
struct Element;

template<template<typename...> typename TypeList, size_t Index, typename Head, typename... Tail>
struct Element<TypeList<Head, Tail...>, Index> : Element<TypeList<Tail...>, Index - 1>
{
    static_assert(Index <= sizeof...(Tail), "out of range.");
};

template<template<typename...> typename TypeList, typename Head, typename... Rest>
struct Element<TypeList<Head, Rest...>, 0>
{
    using Type = Head;
};

template<typename TypeList, size_t Index>
using Element_t = typename Element<TypeList, Index>::Type;

template<typename TypeList>
struct NumElement;

template<template<typename...> typename TypeList, typename... Args>
struct NumElement<TypeList<Args...>>
{
    static constexpr size_t value = sizeof...(Args);
};

template<typename TypeList>
inline constexpr size_t NumElement_v = NumElement<TypeList>::value;

template<typename TypeList, typename T>
struct IsContains;

template<template<typename...> typename TypeList, typename... T, typename U>
struct IsContains<TypeList<T...>, U> : std::bool_constant<(std::is_same<T, U>::value || ...)>
{
};

template<typename TypeList, typename T>
inline constexpr bool IsContains_v = IsContains<TypeList, T>::value;

static size_t MakeTypeId() noexcept
{
    static std::atomic<size_t> id = 0;
    return id++;
}

template<class T>
static const size_t GetTypeId() noexcept
{
    static const auto id = MakeTypeId();
    return id;
}

template<typename TypeList, size_t... N>
void PrintTypeId_impl(std::index_sequence<N...>)
{
    using swallow = std::initializer_list<int>;
    (void)swallow {
        (std::cout << GetTypeId<Element_t<TypeList, N>>() << ", ", 0)...
    };
    std::cout << std::endl;
}

template<typename TypeList>
void PrintTypeId()
{
    PrintTypeId_impl<TypeList>(std::make_index_sequence<NumElement_v<TypeList>>{});
}

template<class... Args>
struct Archetype
{
};

struct A
{
    int value;
};

struct B
{
    float value;
};

struct C
{
    char value;
};

int main(int, char**)
{
    PrintTypeId<Archetype<A, B, C>>();
    PrintTypeId<Archetype<C, A>>();
    PrintTypeId<Archetype<B, A>>();

    static_assert(NumElement_v<Archetype<A, B, C>> == 3, "");
    static_assert(IsContains_v<Archetype<A, B, C>, A>, "");

    return 0;
}
