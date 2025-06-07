#pragma once

#include "Entity.h"

namespace ECS {

struct EntityDataLocation;

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

	const T* operator[](size_t index) const noexcept
	{
		if (index >= m_size)
			return nullptr;

		return m_begin + index;
	}

	T* operator[](size_t index) noexcept
	{
		return const_cast<T*>(std::as_const(*this)[index]);
	}

	const T* begin() const noexcept
	{
		return m_begin;
	}

	const T* end() const noexcept
	{
		return m_begin + m_size;
	}

	T* begin() noexcept
	{
		return const_cast<T*>(std::as_const(*this).begin());
	}

	T* end() noexcept
	{
		return const_cast<T*>(std::as_const(*this).end());
	}

private:
	T*     m_begin;
	size_t m_size;
};

//! \brief 特定のエンティティが持つコンポーネントデータの集合
class ComponentDataGroup
{
public:
	ComponentDataGroup(EntityDataLocation* location);

private:
	EntityDataLocation* m_location;
};

} // namespace ECS
