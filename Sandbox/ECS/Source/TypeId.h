#pragma once

#include <cstdint>

namespace ECS {

//! \brief 特定の型を表す一意な識別子
using TypeId = uint32_t;

namespace Internal {

enum class TypeIdTag
{
	kComponent = 1,
	kSharedComponent,
	kSystem,
};

template<TypeIdTag Tag>
struct TypeIdTraits
{
	static constexpr TypeIdTag kTag = Tag;
};

template<TypeIdTag Tag>
TypeId MakeTypeId() noexcept;

template TypeId MakeTypeId<TypeIdTag::kComponent>() noexcept;
template TypeId MakeTypeId<TypeIdTag::kSharedComponent>() noexcept;
template TypeId MakeTypeId<TypeIdTag::kSystem>() noexcept;

uint32_t GetTypeIndex(TypeId id) noexcept;

} // namespace Internal
} // namespace ECS
