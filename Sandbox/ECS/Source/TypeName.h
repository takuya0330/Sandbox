#pragma once

#include "TypeNameInternal.h"

#include <type_traits>

namespace ECS {

//! \brief 型名を取得する
template<typename T>
constexpr const char* TypeNameOf() noexcept
{
	return Internal::name_of_impl<std::remove_cvref_t<T>>().data();
}

} // namespace ECS
