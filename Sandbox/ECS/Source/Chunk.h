#pragma once

#include "ComponentType.h"

#include <memory>

namespace ECS {

class Archetype;

class Chunk
{
public:
	Chunk(Archetype* archetype);

    bool IsFull() const noexcept;

    uint32_t IncEntityCount() noexcept;

	const uint8_t* GetDataArray(TypeId id) const;

	uint8_t* GetDataArray(TypeId id)
	{
		return const_cast<uint8_t*>(std::as_const(*this).GetDataArray(id));
	}

	template<ComponentDataType T>
	const T* GetDataArray() const
	{
		return reinterpret_cast<const T*>(GetDataArray(GetComponentTypeId<T>()));
	}

	template<ComponentDataType T>
	T* GetDataArray()
	{
		return const_cast<T*>(std::as_const(*this).GetDataArray<T>());
	}

	template<ComponentDataType T>
	const T* GetData(uint32_t index) const
	{
		const T* arr = GetDataArray<T>();
		if (!arr)
			return nullptr;

		return arr + index;
	}

	template<ComponentDataType T>
	T* GetData(uint32_t index)
	{
		return const_cast<T*>(std::as_const(*this).GetData<T>(index));
	}

private:
	const Archetype*           m_parent;
	std::unique_ptr<uint8_t[]> m_memory;
	uint32_t                   m_entity_count;
};

} // namespace ECS
