#pragma once

#include "TypeId.h"

namespace ECS {

//! \brief コンポーネントの型識別子
using ComponentTypeId = TypeId;

//! \brief 共有コンポーネントの型識別子
using SharedComponentTypeId = TypeId;

template< typename T >
static const ComponentTypeId GetComponentTypeId() noexcept
{
	static const auto id = Internal::MakeTypeId< Internal::TypeIdTag::kComponent >();
	return id;
}

template< typename T >
static const SharedComponentTypeId GetSharedComponentTypeId() noexcept
{
	static const auto id = Internal::MakeTypeId< Internal::TypeIdTag::kSharedComponent >();
	return id;
}

} // namespace ECS
