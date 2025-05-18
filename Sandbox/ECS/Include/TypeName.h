#pragma once

#include "TypeNameInternal.h"

namespace ECS {

//! \brief 型名を取得する
template<typename T>
constexpr const char* TypeNameOf()
{
	return Internal::name_of_impl<T>().data();
}

} // namespace ECS
