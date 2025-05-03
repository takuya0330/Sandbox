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
concept NameGetable = requires {
	T::GetName();
};

} // namespace Internal

using IComponentData = Internal::TypeIdTraits<Internal::Metadata::kComponent>;

using ISharedComponentData = Internal::TypeIdTraits<Internal::Metadata::kSharedComponent>;

template<typename T>
concept ComponentDataType = requires {
	requires std::is_base_of_v<IComponentData, T> || std::is_base_of_v<ISharedComponentData, T>;
	requires std::is_trivial_v<T>;
	requires std::is_trivially_destructible_v<T>;
	requires std::is_move_constructible_v<T>;
	requires Internal::NameGetable<T>;
};

template<ComponentDataType T>
static const TypeId GetComponentTypeId() noexcept
{
	static const auto id = Internal::MakeTypeId<T::kMeta>();
	return id;
}

struct ComponentType
{
	const char* name;
	TypeId      id;
	size_t      size;
	size_t      alignment;

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
		T::GetName().data(),
		GetComponentTypeId<T>(),
		sizeof(T),
		alignof(T)
	};
}

} // namespace ECS
