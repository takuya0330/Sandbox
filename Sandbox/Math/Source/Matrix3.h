#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Matrix3
{
	using Type    = T;
	using RowType = Vector3< T >;

	union
	{
		struct
		{
			Type _11, _12, _13;
			Type _21, _22, _23;
			Type _31, _32, _33;
		};
		Type    m[3][3];
		RowType r[3];
	};

	constexpr Matrix3() = default;

	constexpr Matrix3(const Matrix3&) = default;

	constexpr Matrix3(Matrix3&&) = default;

	constexpr Matrix3& operator=(const Matrix3&) = default;

	constexpr Matrix3& operator=(Matrix3&&) = default;

	// clang-format off

	constexpr Matrix3(
        Type _11, Type _12, Type _13,
        Type _21, Type _22, Type _23,
        Type _31, Type _32, Type _33) noexcept
	    : _11(_11), _12(_12), _13(_13)
	    , _21(_21), _22(_22), _23(_23)
	    , _31(_31), _32(_32), _33(_33)
	{
	}

	constexpr Matrix3(const RowType& r0, const RowType& r1, const RowType& r2) noexcept
	    : _11(r0.x), _12(r0.y), _13(r0.z)
	    , _21(r1.x), _22(r1.y), _23(r1.z)
	    , _31(r2.x), _32(r2.y), _33(r2.z)
	{
	}

	template<
        class T11, class T12, class T13,
        class T21, class T22, class T23,
        class T31, class T32, class T33>
	constexpr Matrix3(
        T11 _11, T12 _12, T13 _13,
        T21 _21, T22 _22, T23 _23,
        T31 _31, T32 _32, T33 _33) noexcept
	    : _11(static_cast<Type>(_11)), _12(static_cast<Type>(_12)), _13(static_cast<Type>(_13))
	    , _21(static_cast<Type>(_21)), _22(static_cast<Type>(_22)), _23(static_cast<Type>(_23))
	    , _31(static_cast<Type>(_31)), _32(static_cast<Type>(_32)), _33(static_cast<Type>(_33))
	{
	}

	template<class R0, class R1, class R2>
	constexpr Matrix3(const Vector3<R0>& r0, const Vector3<R1>& r1, const Vector3<R2>& r2) noexcept
	    : _11(static_cast<Type>(r0.x)), _12(static_cast<Type>(r0.y)), _13(static_cast<Type>(r0.z))
	    , _21(static_cast<Type>(r1.x)), _22(static_cast<Type>(r1.y)), _23(static_cast<Type>(r1.z))
	    , _31(static_cast<Type>(r2.x)), _32(static_cast<Type>(r2.y)), _33(static_cast<Type>(r2.z))
	{
	}

	template<class U>
	constexpr Matrix3(const Matrix3<U>& m) noexcept
	    : _11(static_cast<Type>(m._11)), _12(static_cast<Type>(m._12)), _13(static_cast<Type>(m._13))
	    , _21(static_cast<Type>(m._21)), _22(static_cast<Type>(m._22)), _23(static_cast<Type>(m._23))
	    , _31(static_cast<Type>(m._31)), _32(static_cast<Type>(m._32)), _33(static_cast<Type>(m._33))
	{
	}

	// clang-format on

	constexpr bool operator==(const Matrix3& m) const noexcept
	{
		return r[0] == m.r[0] && r[1] == m.r[1] && r[2] == m.r[2];
	}

	constexpr bool operator!=(const Matrix3& m) const noexcept
	{
		return !(*this == m);
	}
};

} // namespace Math
