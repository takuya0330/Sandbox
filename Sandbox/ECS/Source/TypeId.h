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

template<Metadata Tag>
TypeId MakeTypeId() noexcept;

template TypeId MakeTypeId<Metadata::kComponent>() noexcept;
template TypeId MakeTypeId<Metadata::kSharedComponent>() noexcept;
template TypeId MakeTypeId<Metadata::kSystem>() noexcept;

uint32_t GetTypeIndex(TypeId id) noexcept;

} // namespace Internal
} // namespace ECS
