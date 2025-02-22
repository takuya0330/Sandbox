#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Matrix4
{
	using Type    = T;
	using RowType = Vector4< T >;

	union
	{
		struct
		{
			Type _11, _12, _13, _14;
			Type _21, _22, _23, _24;
			Type _31, _32, _33, _34;
			Type _41, _42, _43, _44;
		};
		Type    m[4][4];
		RowType r[4];
	};

	constexpr Matrix4() = default;

	constexpr Matrix4(const Matrix4&) = default;

	constexpr Matrix4(Matrix4&&) = default;

	constexpr Matrix4& operator=(const Matrix4&) = default;

	constexpr Matrix4& operator=(Matrix4&&) = default;

	// clang-format off

	constexpr Matrix4(
        Type _11, Type _12, Type _13, Type _14,
        Type _21, Type _22, Type _23, Type _24,
        Type _31, Type _32, Type _33, Type _34,
        Type _41, Type _42, Type _43, Type _44) noexcept
	    : _11(_11), _12(_12), _13(_13), _14(_14)
	    , _21(_21), _22(_22), _23(_23), _24(_24)
	    , _31(_31), _32(_32), _33(_33), _34(_34)
	    , _41(_41), _42(_42), _43(_43), _44(_44)
	{
	}

	constexpr Matrix4(const RowType& r0, const RowType& r1, const RowType& r2, const RowType& r3) noexcept
	    : _11(r0.x), _12(r0.y), _13(r0.z), _14(r0.w)
	    , _21(r1.x), _22(r1.y), _23(r1.z), _24(r1.w)
	    , _31(r2.x), _32(r2.y), _33(r2.z), _34(r2.w)
	    , _41(r3.x), _42(r3.y), _43(r3.z), _44(r3.w)
	{
	}

	template<
        class T11, class T12, class T13, class T14,
        class T21, class T22, class T23, class T24,
        class T31, class T32, class T33, class T34,
        class T41, class T42, class T43, class T44>
	constexpr Matrix4(
        T11 _11, T12 _12, T13 _13, T14 _14,
        T21 _21, T22 _22, T23 _23, T24 _24,
        T31 _31, T32 _32, T33 _33, T34 _34,
        T41 _41, T42 _42, T43 _43, T44 _44) noexcept
	    : _11(static_cast<Type>(_11)), _12(static_cast<Type>(_12)), _13(static_cast<Type>(_13)), _14(static_cast<Type>(_14))
	    , _21(static_cast<Type>(_21)), _22(static_cast<Type>(_22)), _23(static_cast<Type>(_23)), _24(static_cast<Type>(_24))
	    , _31(static_cast<Type>(_31)), _32(static_cast<Type>(_32)), _33(static_cast<Type>(_33)), _34(static_cast<Type>(_34))
	    , _41(static_cast<Type>(_41)), _42(static_cast<Type>(_42)), _43(static_cast<Type>(_43)), _44(static_cast<Type>(_44))
	{
	}

	template<class R0, class R1, class R2, class R3>
	constexpr Matrix4(const Vector4<R0>& r0, const Vector4<R1>& r1, const Vector4<R2>& r2, const Vector4<R3>& r3) noexcept
	    : _11(static_cast<Type>(r0.x)), _12(static_cast<Type>(r0.y)), _13(static_cast<Type>(r0.z)), _14(static_cast<Type>(r0.w))
	    , _21(static_cast<Type>(r1.x)), _22(static_cast<Type>(r1.y)), _23(static_cast<Type>(r1.z)), _24(static_cast<Type>(r1.w))
	    , _31(static_cast<Type>(r2.x)), _32(static_cast<Type>(r2.y)), _33(static_cast<Type>(r2.z)), _34(static_cast<Type>(r2.w))
	    , _41(static_cast<Type>(r3.x)), _42(static_cast<Type>(r3.y)), _43(static_cast<Type>(r3.z)), _44(static_cast<Type>(r3.w))
	{
	}

	template<class U>
	constexpr Matrix4(const Matrix4<U>& m) noexcept
	    : _11(static_cast<Type>(m._11)), _12(static_cast<Type>(m._12)), _13(static_cast<Type>(m._13)), _14(static_cast<Type>(m._14))
	    , _21(static_cast<Type>(m._21)), _22(static_cast<Type>(m._22)), _23(static_cast<Type>(m._23)), _24(static_cast<Type>(m._24))
	    , _31(static_cast<Type>(m._31)), _32(static_cast<Type>(m._32)), _33(static_cast<Type>(m._33)), _34(static_cast<Type>(m._34))
	    , _41(static_cast<Type>(m._41)), _42(static_cast<Type>(m._42)), _43(static_cast<Type>(m._43)), _44(static_cast<Type>(m._44))
	{
	}

	constexpr bool operator==(const Matrix4& m) const noexcept
	{
		return r[0] == m.r[0] && r[1] == m.r[1] && r[2] == m.r[2] && r[3] == m.r[3];
	}

	constexpr bool operator!=(const Matrix4& m) const noexcept
	{
		return !(*this == m);
	}
};

} // namespace Math
