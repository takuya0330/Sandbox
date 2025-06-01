#pragma once

#include "TypeInfo.h"

namespace ECS {

//! \brief 全てのコンポーネントデータの制約
template<typename T>
concept ComponentDataType = requires {
	requires std::is_trivially_copyable_v<T>;
	requires std::is_standard_layout_v<T>;
};

//! \brief コンポーネントデータのメモリ領域
struct ComponentDataChunk
{
	uint32_t entity_count;
	uint32_t allocator_index;

	const uint8_t* memory() const
	{
		return (uint8_t*)this + sizeof(ComponentDataChunk);
	}

	uint8_t* memory()
	{
		return const_cast<uint8_t*>(std::as_const(*this).memory());
	}
};

//! \brief コンポーネントデータの型情報
struct ComponentType
{
	const char* name;
	TypeIndex   index;
	size_t      size;
	size_t      alignment;

	inline constexpr bool operator==(const ComponentType& c) const noexcept
	{
		return index == c.index && size == c.size && alignment == c.alignment;
	}

	inline constexpr bool operator!=(const ComponentType& c) const noexcept
	{
		return !(*this == c);
	}
};

//! \brief コンポーネントデータの型情報を取得
template<ComponentDataType T>
constexpr ComponentType GetComponentType() noexcept
{
	return {
		TypeInfo<T>::GetTypeName().data(),
		TypeInfo<T>::GetTypeIndex(),
		sizeof(T),
		alignof(T)
	};
}

} // namespace ECS
