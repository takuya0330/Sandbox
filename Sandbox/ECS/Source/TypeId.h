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

template< TypeIdTag Tag >
TypeId MakeTypeId() noexcept;

template TypeId MakeTypeId< TypeIdTag::kComponent >() noexcept;
template TypeId MakeTypeId< TypeIdTag::kSharedComponent >() noexcept;
template TypeId MakeTypeId< TypeIdTag::kSystem >() noexcept;

} // namespace Internal
} // namespace ECS
