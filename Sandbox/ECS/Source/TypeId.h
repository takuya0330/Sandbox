#pragma once

#include <cstdint>

namespace ECS {

//! \brief 特定の型を表す一意な識別子
using TypeId = uint32_t;

namespace Internal {

enum class Metadata
{
	kComponent = 1,
	kSharedComponent,
	kSystem,
};

template<Metadata Meta>
struct TypeIdTraits
{
	static constexpr Metadata kMeta = Meta;
};

TypeId MakeTypeId(Metadata meta) noexcept;

uint32_t GetTypeIndex(TypeId id) noexcept;

template<typename T>
struct TypeIdResolver
{
	inline static const TypeId id = MakeTypeId(T::kMeta);
};

} // namespace Internal
} // namespace ECS
