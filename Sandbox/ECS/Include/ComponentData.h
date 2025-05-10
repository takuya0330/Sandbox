#pragma once

#include "TypeId.h"

#include <type_traits>

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

//! \brief コンポーネントデータの一意な識別子を取得
template<ComponentDataType T>
static const TypeId GetComponentDataTypeId() noexcept
{
	return Internal::TypeIdResolver<std::remove_cvref_t<T>, Internal::TypeIdMetadata::kComponentData>::id;
}

} // namespace ECS
