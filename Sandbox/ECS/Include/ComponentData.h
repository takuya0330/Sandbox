#pragma once

#include "TypeId.h"
#include "TypeName.h"

#define ECS_DECLARE_COMPONENT_DATA(Type, ...)  \
	struct Type : ECS::IComponentData          \
	{                                          \
		__VA_ARGS__;                           \
	};                                         \
	constexpr std::string_view _name_of(Type*) \
	{                                          \
		return #Type;                          \
	}

namespace ECS {

struct IComponentData;

//! \brief 全てのコンポーネントデータの制約
template<typename T>
concept ComponentDataType = requires {
	requires std::is_base_of_v<IComponentData, T>;
	requires std::is_trivial_v<T>;
	requires std::is_trivially_destructible_v<T>;
	requires std::is_move_constructible_v<T>;
};

//! \brief 全てのコンポーネントデータの基底構造体
struct IComponentData
{
};

//! \brief コンポーネントデータの型情報
struct ComponentType
{
	TypeId id;
	size_t size;
	size_t alignment;

	inline constexpr bool operator==(const ComponentType& c) const noexcept
	{
		return id == c.id && size == c.size && alignment == c.alignment;
	}

	inline constexpr bool operator!=(const ComponentType& c) const noexcept
	{
		return !(*this == c);
	}
};

//! \brief コンポーネントデータの型情報を取得
template<ComponentDataType T>
static const ComponentType GetComponentType() noexcept
{
	return {
		TypeIdOf<T>(),
		sizeof(T),
		alignof(T)
	};
}

} // namespace ECS
