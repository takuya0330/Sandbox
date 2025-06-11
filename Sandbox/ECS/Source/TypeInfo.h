#pragma once

#include <cstdint>

namespace ECS {

using TypeIndex = uint32_t;

struct TypeInfoTraits
{
	using NameType  = const char*;
	using IndexType = TypeIndex;

	static const NameType GetTypeName() noexcept
	{
		return "Unknown";
	}

	static const IndexType GetTypeIndex() noexcept
	{
		return static_cast<IndexType>(-1);
	}
};

template<typename T, typename Traits = TypeInfoTraits>
struct TypeInfo
{
	using NameType  = typename Traits::NameType;
	using IndexType = typename Traits::IndexType;

	static const NameType GetTypeName() noexcept
	{
		return Traits::GetTypeName();
	}
	static const IndexType GetTypeIndex() noexcept
	{
		return Traits::GetTypeIndex();
	}
};

} // namespace ECS
