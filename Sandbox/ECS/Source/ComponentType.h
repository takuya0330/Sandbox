#pragma once

#include "TypeId.h"

#include <string_view>
#include <type_traits>

#define ECS_COMPONENT_DATA(Type)                         \
	static constexpr std::string_view GetName() noexcept \
	{                                                    \
		return #Type;                                    \
	}

namespace ECS {
namespace Internal {

template<typename T>
struct has_member_function_get_name
{
	template<typename X, int = (&X::GetName, 0)>
	static std::true_type test(X*);

	static std::false_type test(...);

	static constexpr bool value = decltype(test((T*)nullptr))::value;
};

template<typename T>
static constexpr bool has_member_function_get_name_v = has_member_function_get_name<T>::value;

} // namespace Internal

using IComponentData = Internal::TypeIdTraits<Internal::TypeIdTag::kComponent>;

using ISharedComponentData = Internal::TypeIdTraits<Internal::TypeIdTag::kSharedComponent>;

template<typename T>
concept ComponentDataType = requires {
	requires std::is_base_of_v<IComponentData, T> || std::is_base_of_v<ISharedComponentData, T>;
	requires std::is_trivial_v<T>;
	requires std::is_trivially_destructible_v<T>;
	requires std::is_move_constructible_v<T>;
	requires Internal::has_member_function_get_name_v<T>;
};

template<ComponentDataType T>
static const TypeId GetComponentTypeId() noexcept
{
	static const auto id = Internal::MakeTypeId<T::kTag>();
	return id;
}

struct ComponentType
{
	TypeId      id;
	size_t      size;
	size_t      alignment;
	const char* name;

	inline constexpr bool operator==(const ComponentType& c) const noexcept
	{
		return id == c.id && size == c.size && alignment == c.alignment;
	}

	inline constexpr bool operator!=(const ComponentType& c) const noexcept
	{
		return !(*this == c);
	}
};

template<ComponentDataType T>
const ComponentType GetComponentType() noexcept
{
	return {
		GetComponentTypeId<T>(), sizeof(T), alignof(T), T::GetName().data()
	};
}

} // namespace ECS
