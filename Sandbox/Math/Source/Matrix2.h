#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Matrix2
{
	using Type    = T;
	using RowType = Vector2< T >;

	union
	{
		struct
		{
			Type _11, _12;
			Type _21, _22;
		};
		Type    m[2][2];
		RowType r[2];
	};

	constexpr Matrix2() = default;

	constexpr Matrix2(const Matrix2&) = default;

	constexpr Matrix2(Matrix2&&) = default;

	constexpr Matrix2& operator=(const Matrix2&) = default;

	constexpr Matrix2& operator=(Matrix2&&) = default;

	// clang-format off

	constexpr Matrix2(
        Type _11, Type _12,
        Type _21, Type _22) noexcept
	    : _11(_11), _12(_12)
	    , _21(_21), _22(_22)
	{
	}

	constexpr Matrix2(const RowType& r0, const RowType& r1) noexcept
	    : _11(r0.x), _12(r0.y)
	    , _21(r1.x), _22(r1.y)
	{
	}

	template<
        class T11, class T12,
        class T21, class T22>
	constexpr Matrix2(
        T11 _11, T12 _12,
        T21 _21, T22 _22) noexcept
	    : _11(static_cast<Type>(_11)), _12(static_cast<Type>(_12))
	    , _21(static_cast<Type>(_21)), _22(static_cast<Type>(_22))
	{
	}

	template<class R0, class R1>
	constexpr Matrix2(const Vector2<R0>& r0, const Vector2<R1>& r1) noexcept
	    : _11(static_cast<Type>(r0.x)), _12(static_cast<Type>(r0.y))
	    , _21(static_cast<Type>(r1.x)), _22(static_cast<Type>(r1.y))
	{
	}

	template<class U>
	constexpr Matrix2(const Matrix2<U>& m) noexcept
	    : _11(static_cast<Type>(m._11)), _12(static_cast<Type>(m._12))
	    , _21(static_cast<Type>(m._21)), _22(static_cast<Type>(m._22))
	{
	}

	// clang-format on

	constexpr bool operator==(const Matrix2& m) const noexcept
	{
		return r[0] == m.r[0] && r[1] == m.r[1];
	}

	constexpr bool operator!=(const Matrix2& m) const noexcept
	{
		return !(*this == m);
	}
};

} // namespace Math
