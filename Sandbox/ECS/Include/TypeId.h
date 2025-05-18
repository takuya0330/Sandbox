#pragma once

#include "TypeIdInternal.h"

#include <type_traits>

namespace ECS {

//! \brief 特定の型を表す一意な識別子
using TypeId = uint32_t;

template<typename T>
constexpr TypeId TypeIdOf() noexcept
{
	return Internal::typeid_of_impl<std::remove_cvref_t<T>>();
}

} // namespace ECS
