#pragma once

#include <type_traits>

#include "TypeId.h"

namespace ECS {
namespace Internal {

template< TypeIdTag Tag >
struct ComponentDataTraits
{
	static constexpr TypeIdTag kTag = Tag;
};

} // namespace Internal

using IComponentData = Internal::ComponentDataTraits< Internal::TypeIdTag::kComponent >;

using ISharedComponentData = Internal::ComponentDataTraits< Internal::TypeIdTag::kSharedComponent >;

template< typename T >
concept ComponentDataType = requires {
	requires std::is_base_of_v< IComponentData, T > || std::is_base_of_v< ISharedComponentData, T >;
	requires std::is_trivial_v< T >;
	requires std::is_trivially_destructible_v< T >;
	requires std::is_move_constructible_v< T >;
};

template< ComponentDataType T >
static const TypeId GetComponentTypeId() noexcept
{
	static const auto id = Internal::MakeTypeId< T::kTag >();
	return id;
}

struct ComponentType
{
	TypeId id;
	size_t size;
	size_t alignment;
};

template< ComponentDataType T >
const ComponentType GetComponentType() noexcept
{
	return {
		GetComponentTypeId< T >(), sizeof(T), alignof(T)
	};
}

} // namespace ECS
