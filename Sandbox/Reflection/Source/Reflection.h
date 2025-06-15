#pragma once

#include <tuple>

template<typename T>
concept Reflectable = requires {
	T::Fields();
};

template<typename T>
struct Reflection
{
	static constexpr auto Fields()
	{
		return T::Fields();
	}

	template<size_t N>
	static constexpr auto Field()
	{
		return std::get<N>(Fields());
	}

	template<typename Function>
	static void Reflect(T& obj, Function&& func)
	{
		std::apply([&](auto&&... pair)
		    {
			    (func(pair.first, obj.*(pair.second)), ...);
		    },
		    Fields());
	}
};

template<typename T, typename Function>
static void Reflect(T& obj, Function&& func)
{
	Reflection<T>::Reflect(obj, [&](auto name, auto& field)
	    {
		    if constexpr (Reflectable<std::decay_t<decltype(field)>>)
		    {
			    Reflect(field, std::forward<Function>(func));
		    }
		    else
		    {
			    func(name, field);
		    }
	    });
}

#define REFLECTION(Type, ...)                \
	using This = Type;                       \
	friend struct Reflection<This>;          \
	static constexpr auto Fields()           \
	{                                        \
		return std::make_tuple(__VA_ARGS__); \
	}

#define REFLECT_FIELD(Member) \
	REFLECT_FIELD_IMPL(This, Member)

#define REFLECT_FIELD_WITH_NAME(Name, Member) \
	REFLECT_FIELD_WITH_NAME_IMPL(Name, This, Member)

#define REFLECT_FIELD_IMPL(Type, Member) \
	std::make_pair(#Member, &Type::Member)

#define REFLECT_FIELD_WITH_NAME_IMPL(Name, Type, Member) \
	std::make_pair(#Name, &Type::Member)
