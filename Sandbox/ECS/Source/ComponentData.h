#pragma once

#include "TypeInfo.h"

#include <memory>
#include <type_traits>
#include <utility>

namespace ECS {

//! \brief コンポーネントデータの最大チャンクサイズ
constexpr size_t kMaxChunkSize = 16 * 1024;

//! \brief 全てのコンポーネントデータの制約
template<typename T>
concept ComponentDataType = requires {
	requires std::is_trivially_copyable_v<T>;
	requires std::is_standard_layout_v<T>;
};

//! \brief 特定の型のコンポーネントデータ配列
template<ComponentDataType T>
class ComponentDataArray
{
public:
	ComponentDataArray(T* begin, size_t size) noexcept
	    : m_begin(begin)
	    , m_size(size)
	{
	}

	T* operator[](size_t index) noexcept
	{
		if (index >= m_size)
			return nullptr;

		return m_begin + index;
	}

	T* begin() noexcept
	{
		return m_begin;
	}

	T* end() noexcept
	{
		return m_begin + m_size;
	}

private:
	T*     m_begin;
	size_t m_size;
};

//! \brief コンポーネントデータチャンク
struct ComponentDataChunk
{
	std::unique_ptr<uint8_t[]> buffer;
	uint32_t                   entity_count;
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
		TypeInfo<T>::GetTypeName(),
		TypeInfo<T>::GetTypeIndex(),
		sizeof(T),
		alignof(T)
	};
}

} // namespace ECS
