#pragma once

#include <cmath>
#include <limits>

// clang-format off

#include "Types.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"

// clang-format on

namespace Math {

template< class T >
constexpr T kInfinity = std::numeric_limits< T >::infinity();

template< class T >
constexpr T kEpsilon = std::numeric_limits< T >::epsilon();

template< class T >
constexpr T kPI = static_cast< T >(3.141592653589793238);

template< class T, size_t Size >
constexpr size_t ArrayOf(T (&array)[Size])
{
	return Size;
}

template< class T >
constexpr T Deg2Rad(T degree)
{
	return degree * (kPI< T > / static_cast< T >(180));
}

template< class T >
constexpr T Rad2Deg(T radian)
{
	return radian * (static_cast< T >(180) / kPI< T >);
}

#if 0
template< class T >
constexpr Vector2< T >(Min)(const Vector2< T >& a, const Vector2< T >& b)
{
	return Vector2< T >((std::min)(a.x, b.x), (std::min)(a.y, b.y));
}

template< class T >
constexpr Vector3< T >(Min)(const Vector3< T >& a, const Vector3< T >& b)
{
	return Vector3< T >((std::min)(a.x, b.x), (std::min)(a.y, b.y), (std::min)(a.z, b.z));
}

template< class T >
constexpr Vector4< T >(Min)(const Vector4< T >& a, const Vector4< T >& b)
{
	return Vector4< T >((std::min)(a.x, b.x), (std::min)(a.y, b.y), (std::min)(a.z, b.z), (std::min)(a.w, b.w));
}

template< class T >
constexpr Vector2< T >(Max)(const Vector2< T >& a, const Vector2< T >& b)
{
	return Vector2< T >((std::max)(a.x, b.x), (std::max)(a.y, b.y));
}

template< class T >
constexpr Vector3< T >(Max)(const Vector3< T >& a, const Vector3< T >& b)
{
	return Vector3< T >((std::max)(a.x, b.x), (std::max)(a.y, b.y), (std::max)(a.z, b.z));
}

template< class T >
constexpr Vector4< T >(Max)(const Vector4< T >& a, const Vector4< T >& b)
{
	return Vector4< T >((std::max)(a.x, b.x), (std::max)(a.y, b.y), (std::max)(a.z, b.z), (std::max)(a.w, b.w));
}
#endif

template< class T >
constexpr Vector2< T > Abs(const Vector2< T >& a)
{
	return Vector2< T >(a.x < 0 ? -a.x : a.x, a.y < 0 ? -a.y : a.y);
}

template< class T >
constexpr Vector3< T > Abs(const Vector3< T >& a)
{
	return Vector3< T >(a.x < 0 ? -a.x : a.x, a.y < 0 ? -a.y : a.y, a.z < 0 ? -a.z : a.z);
}

template< class T >
constexpr Vector4< T > Abs(const Vector4< T >& a)
{
	return Vector4< T >(a.x < 0 ? -a.x : a.x, a.y < 0 ? -a.y : a.y, a.z < 0 ? -a.z : a.z, a.w < 0 ? -a.w : a.w);
}

template< typename T >
constexpr T Clamp(T val, T min, T max)
{
	return val < min ? min : (val > max ? max : val);
}

template< class T >
constexpr Vector2< T > Clamp(const Vector2< T >& a, const Vector2< T >& min, const Vector2< T >& max)
{
	return Vector2< T >(Clamp(a.x, min.x, max.x), Clamp(a.y, min.y, max.y));
}

template< class T >
constexpr Vector3< T > Clamp(const Vector3< T >& a, const Vector3< T >& min, const Vector3< T >& max)
{
	return Vector3< T >(Clamp(a.x, min.x, max.x), Clamp(a.y, min.y, max.y), Clamp(a.z, min.z, max.z));
}

template< class T >
constexpr Vector4< T > Clamp(const Vector4< T >& a, const Vector4< T >& min, const Vector4< T >& max)
{
	return Vector4< T >(Clamp(a.x, min.x, max.x), Clamp(a.y, min.y, max.y), Clamp(a.z, min.z, max.z), Clamp(a.w, min.w, max.w));
}

template< class T >
constexpr T Dot(const Vector2< T >& a, const Vector2< T >& b)
{
	return a.x * b.x + a.y * b.y;
}

template< class T >
constexpr T Dot(const Vector3< T >& a, const Vector3< T >& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template< class T >
constexpr T Dot(const Vector4< T >& a, const Vector4< T >& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template< class Vector >
constexpr auto Length(const Vector& v) -> decltype(Dot(v, v))
{
	return sqrt(Dot(v, v));
}

template< class Vector >
constexpr auto Normalize(const Vector& v)
{
	return v / Length(v);
}

template< class T >
constexpr Vector3< T > Cross(const Vector3< T >& a, const Vector3< T >& b)
{
	return Vector3< T >((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
}

template< class T >
constexpr Matrix2< T > Identity()
{
	// clang-format off
    return {
        1, 0,
        0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > Identity()
{
	// clang-format off
	return {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Identity()
{
	// clang-format off
	return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix2< T > Mul(const Matrix2< T >& a, const Matrix2< T >& b)
{
	Matrix2< T > out;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				out.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return out;
}

template< class T >
constexpr Matrix3< T > Mul(const Matrix3< T >& a, const Matrix3< T >& b)
{
	Matrix3< T > out;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				out.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return out;
}

template< class T >
constexpr Matrix4< T > Mul(const Matrix4< T >& a, const Matrix4< T >& b)
{
	Matrix4< T > out;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				out.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return out;
}

template< class T >
constexpr Matrix2< T > Transpose(const Matrix2< T >& m)
{
	// clang-format off
    return {
        m._11, m._21,
        m._12, m._22
    };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > Transpose(const Matrix3< T >& m)
{
	// clang-format off
    return {
        m._11, m._21, m._31,
        m._12, m._22, m._32,
        m._13, m._23, m._33
    };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Transpose(const Matrix4< T >& m)
{
	// clang-format off
    return {
        m._11, m._21, m._31, m._41,
        m._12, m._22, m._32, m._42,
        m._13, m._23, m._33, m._43,
        m._14, m._24, m._34, m._44
    };
	// clang-format on
}

template< class T >
constexpr T Determinant(const Matrix2< T >& m)
{
	return m._11 * m._22 - m._12 * m._21;
}

template< class T >
constexpr T Determinant(const Matrix3< T >& m)
{
	T det = 0;
	det += m._11 * (m._22 * m._33 - m._32 * m._23);
	det -= m._12 * (m._21 * m._33 - m._31 * m._23);
	det += m._13 * (m._21 * m._32 - m._31 * m._22);
	return det;
}

template< class T >
constexpr T Determinant(const Matrix4< T >& m)
{
	T det = 0;
	det += m._11 * Determinant(Matrix3< T >(m._22, m._23, m._24, m._32, m._33, m._34, m._42, m._43, m._44));
	det -= m._12 * Determinant(Matrix3< T >(m._21, m._23, m._24, m._31, m._33, m._34, m._41, m._43, m._44));
	det += m._13 * Determinant(Matrix3< T >(m._21, m._22, m._24, m._31, m._32, m._34, m._41, m._42, m._44));
	det += m._14 * Determinant(Matrix3< T >(m._21, m._22, m._23, m._31, m._32, m._33, m._41, m._42, m._43));
	return det;
}

template< class T >
constexpr Matrix3< T > Inverse(const Matrix3< T >& m)
{
	Matrix3< T > mat;

	// clang-format off
	mat._11 =  Determinant(Matrix2<T>(m._22, m._23, m._32, m._33));
	mat._12 = -Determinant(Matrix2<T>(m._21, m._23, m._31, m._33));
	mat._13 =  Determinant(Matrix2<T>(m._21, m._22, m._31, m._32));
	mat._21 = -Determinant(Matrix2<T>(m._12, m._13, m._32, m._33));
	mat._22 =  Determinant(Matrix2<T>(m._11, m._13, m._31, m._33));
	mat._23 = -Determinant(Matrix2<T>(m._11, m._12, m._31, m._32));
	mat._31 =  Determinant(Matrix2<T>(m._12, m._13, m._22, m._23));
	mat._32 = -Determinant(Matrix2<T>(m._11, m._13, m._21, m._23));
	mat._33 =  Determinant(Matrix2<T>(m._11, m._12, m._21, m._22));
	// clang-format on

	auto det = mat._11 * m._11 + mat._12 * m._12 + mat._13 * m._13;
	det      = static_cast< T >(1) / det;

	auto out = Transpose(mat);
	out.r[0] *= det;
	out.r[1] *= det;
	out.r[2] *= det;

	return out;
}

template< class T >
constexpr Matrix4< T > Inverse(const Matrix4< T >& m)
{
	Matrix4< T > mat;

#if 0
	// clang-format off
	mat._11 =  Determinant(Matrix3<T>(m._22, m._23, m._24, m._32, m._33, m._34, m._42, m._43, m._44));
	mat._12 = -Determinant(Matrix3<T>(m._21, m._23, m._24, m._31, m._33, m._34, m._41, m._43, m._44));
	mat._13 =  Determinant(Matrix3<T>(m._21, m._22, m._24, m._31, m._32, m._34, m._41, m._42, m._44));
    mat._14 = -Determinant(Matrix3<T>(m._21, m._22, m._23, m._31, m._32, m._33, m._41, m._42, m._43));
	mat._21 = -Determinant(Matrix3<T>(m._12, m._13, m._14, m._32, m._33, m._34, m._42, m._43, m._44));
	mat._22 =  Determinant(Matrix3<T>(m._11, m._13, m._14, m._31, m._33, m._34, m._41, m._43, m._44));
	mat._23 = -Determinant(Matrix3<T>(m._11, m._12, m._14, m._31, m._32, m._34, m._41, m._42, m._44));
    mat._24 =  Determinant(Matrix3<T>(m._11, m._12, m._13, m._31, m._32, m._33, m._41, m._42, m._43));
	mat._31 =  Determinant(Matrix3<T>(m._12, m._13, m._14, m._22, m._23, m._24, m._42, m._43, m._44));
	mat._32 = -Determinant(Matrix3<T>(m._11, m._13, m._14, m._21, m._23, m._24, m._41, m._43, m._44));
	mat._33 =  Determinant(Matrix3<T>(m._11, m._12, m._14, m._21, m._22, m._24, m._41, m._42, m._44));
    mat._34 = -Determinant(Matrix3<T>(m._11, m._12, m._13, m._21, m._22, m._23, m._41, m._42, m._43));
    mat._41 = -Determinant(Matrix3<T>(m._12, m._13, m._14, m._22, m._23, m._24, m._32, m._33, m._34));
	mat._42 =  Determinant(Matrix3<T>(m._11, m._13, m._14, m._21, m._23, m._24, m._31, m._33, m._34));
	mat._43 = -Determinant(Matrix3<T>(m._11, m._12, m._14, m._21, m._22, m._24, m._31, m._32, m._34));
    mat._44 =  Determinant(Matrix3<T>(m._11, m._12, m._13, m._21, m._22, m._23, m._31, m._32, m._33));
	// clang-format on

    auto det = mat._11 * m._11 + mat._12 * m._12 + mat._13 * m._13 + mat._14 * m._14;
	det      = static_cast<T>(1) / det;

	auto out = Transpose(mat);
	out.r[0] *= det;
	out.r[1] *= det;
	out.r[2] *= det;
	out.r[3] *= det;

	return out;
#else
	mat._11 = m._22 * m._33 * m._44 + m._23 * m._34 * m._42 + m._24 * m._32 * m._43 - m._24 * m._33 * m._42 - m._23 * m._32 * m._44 - m._22 * m._34 * m._43;
	mat._12 = -m._12 * m._33 * m._44 - m._13 * m._34 * m._42 - m._14 * m._32 * m._43 + m._14 * m._33 * m._42 + m._13 * m._32 * m._44 + m._12 * m._34 * m._43;
	mat._13 = m._12 * m._23 * m._44 + m._13 * m._24 * m._42 + m._14 * m._22 * m._43 - m._14 * m._23 * m._42 - m._13 * m._22 * m._44 - m._12 * m._24 * m._43;
	mat._14 = -m._12 * m._23 * m._34 - m._13 * m._24 * m._32 - m._14 * m._22 * m._33 + m._14 * m._23 * m._32 + m._13 * m._22 * m._34 + m._12 * m._24 * m._33;
	mat._21 = -m._21 * m._33 * m._44 - m._23 * m._34 * m._41 - m._24 * m._31 * m._43 + m._24 * m._33 * m._41 + m._23 * m._31 * m._44 + m._21 * m._34 * m._43;
	mat._22 = m._11 * m._33 * m._44 + m._13 * m._34 * m._41 + m._14 * m._31 * m._43 - m._14 * m._33 * m._41 - m._13 * m._31 * m._44 - m._11 * m._34 * m._43;
	mat._23 = -m._11 * m._23 * m._44 - m._13 * m._24 * m._41 - m._14 * m._21 * m._43 + m._14 * m._23 * m._41 + m._13 * m._21 * m._44 + m._11 * m._24 * m._43;
	mat._24 = m._11 * m._23 * m._34 + m._13 * m._24 * m._31 + m._14 * m._21 * m._33 - m._14 * m._23 * m._31 - m._13 * m._21 * m._34 - m._11 * m._24 * m._33;
	mat._31 = m._21 * m._32 * m._44 + m._22 * m._34 * m._41 + m._24 * m._31 * m._42 - m._24 * m._32 * m._41 - m._22 * m._31 * m._44 - m._21 * m._34 * m._42;
	mat._32 = -m._11 * m._32 * m._44 - m._12 * m._34 * m._41 - m._14 * m._31 * m._42 + m._14 * m._32 * m._41 + m._12 * m._31 * m._44 + m._11 * m._34 * m._42;
	mat._33 = m._11 * m._22 * m._44 + m._12 * m._24 * m._41 + m._14 * m._21 * m._42 - m._14 * m._22 * m._41 - m._12 * m._21 * m._44 - m._11 * m._24 * m._42;
	mat._34 = -m._11 * m._22 * m._34 - m._12 * m._24 * m._31 - m._14 * m._21 * m._32 + m._14 * m._22 * m._31 + m._12 * m._21 * m._34 + m._11 * m._24 * m._32;
	mat._41 = -m._21 * m._32 * m._43 - m._22 * m._33 * m._41 - m._23 * m._31 * m._42 + m._23 * m._32 * m._41 + m._22 * m._31 * m._43 + m._21 * m._33 * m._42;
	mat._42 = m._11 * m._32 * m._43 + m._12 * m._33 * m._41 + m._13 * m._31 * m._42 - m._13 * m._32 * m._41 - m._12 * m._31 * m._43 - m._11 * m._33 * m._42;
	mat._43 = -m._11 * m._22 * m._43 - m._12 * m._23 * m._41 - m._13 * m._21 * m._42 + m._13 * m._22 * m._41 + m._12 * m._21 * m._43 + m._11 * m._23 * m._42;
	mat._44 = m._11 * m._22 * m._33 + m._12 * m._23 * m._31 + m._13 * m._21 * m._32 - m._13 * m._22 * m._31 - m._12 * m._21 * m._33 - m._11 * m._23 * m._32;

	auto det = mat._11 * m._11 + mat._12 * m._21 + mat._13 * m._31 + mat._14 * m._41;
	if (det != 0.0f)
	{
		det = static_cast< T >(1) / det;
		mat.r[0] *= det;
		mat.r[1] *= det;
		mat.r[2] *= det;
		mat.r[3] *= det;
	}

	return mat;
#endif
}

template< class T >
constexpr Matrix2< T > Scale(T x, T y)
{
	// clang-format off
	return {
        x, 0,
        0, y };
	// clang-format on
}

template< class T >
constexpr Matrix2< T > Scale(const Vector2< T >& v)
{
	return Scale(v.x, v.y);
}

template< class T >
constexpr Matrix3< T > Scale(T x, T y, T z)
{
	// clang-format off
	return {
        x, 0, 0, 
        0, y, 0,
        0, 0, z };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > Scale(const Vector3< T >& v)
{
	return Scale(v.x, v.y, v.z);
}

template< class T >
constexpr Matrix4< T > Scale(T x, T y, T z)
{
	// clang-format off
	return {
        x, 0, 0, 0, 
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Scale(const Vector3< T >& v)
{
	return Scale(v.x, v.y, v.z);
}

template< class T >
constexpr Matrix2< T > Rotate(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
         c, s,
        -s, c };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > RotateX(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
        1,  0, 0,
        0,  c, s,
        0, -s, c };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > RotateY(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
        c, 0, -s,
        0, 1,  0,
        s, 0,  c };
	// clang-format on
}

template< class T >
constexpr Matrix3< T > RotateZ(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
         c, s, 0,
        -s, c, 0,
         0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > RotateX(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
        1,  0, 0, 0,
        0,  c, s, 0,
        0, -s, c, 0,
        0,  0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > RotateY(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
        c, 0, -s, 0,
        0, 1,  0, 0,
        s, 0,  c, 0,
        0, 0,  0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > RotateZ(T radian)
{
	auto s = std::sin(radian);
	auto c = std::cos(radian);

	// clang-format off
	return {
         c, s, 0, 0,
        -s, c, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Ratate(const Vector3< T >& axis, T radian)
{
	auto v = Normalize(axis);

	auto ps = std::sin(radian);
	auto pc = std::cos(radian);
	auto nc = 1 - pc;

	Matrix4< T > out;

	out._11 = 1 + nc * (axis.x * axis.x - 1);
	out._12 = axis.z * ps + nc * axis.x * axis.y;
	out._13 = -axis.y * ps + nc * axis.x * axis.z;
	out._41 = 0;
	out._21 = -axis.z * ps + nc * axis.y * axis.x;
	out._22 = 1 + nc * (axis.y * axis.y - 1);
	out._23 = axis.x * ps + nc * axis.y * axis.z;
	out._24 = 0;
	out._31 = axis.y * ps + nc * axis.z * axis.x;
	out._32 = -axis.x * ps + nc * axis.z * axis.y;
	out._33 = 1 + nc * (axis.z * axis.z - 1);
	out._34 = 0;
	out._41 = 0;
	out._42 = 0;
	out._43 = 0;
	out._44 = 1;

	return out;
}

template< class T >
constexpr Matrix4< T > Translate(T x, T y, T z)
{
	// clang-format off
    return {
        1, 0, 0, 0, 
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1 };
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Translate(const Vector3< T >& v)
{
	return Translate(v.x, v.y, v.z);
}

template< class T >
constexpr Matrix4< T > LookAtLH(const Vector3< T >& eye, const Vector3< T >& at, const Vector3< T >& up)
{
	auto axis_z = Normalize(at - eye);
	auto axis_x = Normalize(Cross(up, axis_z));
	auto axis_y = Normalize(Cross(axis_z, axis_x));

	// clang-format off
	return {
                 axis_x.x,          axis_y.x,          axis_z.x, 0,
                 axis_x.y,          axis_y.y,          axis_z.y, 0,
                 axis_x.z,          axis_y.z,          axis_z.z, 0,
        -Dot(axis_x, eye), -Dot(axis_y, eye), -Dot(axis_z, eye), 1
	};
	// clang-format on
}

template< class T >
constexpr Matrix4< T > PerspectiveFovLH(T fov, T aspect, T zn, T zf)
{
	auto theta = Deg2Rad(fov);
	auto h     = static_cast< T >(1.0) / tan(theta * 0.5);
	auto w     = h / aspect;
	auto r     = zf / (zf - zn);

	// clang-format off
	return {
		w, 0,       0, 0,
        0, h,       0, 0,
        0, 0,       r, 1,
        0, 0, -r * zn, 0
	};
	// clang-format on
}

template< class T >
constexpr Matrix4< T > Orthographic(T width, T height, T zn, T zf)
{
	auto w = static_cast< T >(2) / width;
	auto h = static_cast< T >(2) / height;
	auto r = zf / (zf - zn);

	// clang-format off
	return {
		w, 0,       0, 0,
        0, h,       0, 0,
        0, 0,       r, 0,
        0, 0, -r * zn, 1
	};
	// clang-format on
}

template< class T >
constexpr Vector3< T > operator*(const Matrix3< T >& m, const Vector3< T >& v)
{
	Vector3< T > out;
	out.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	out.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	out.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	return out;
}

template< class T >
constexpr Vector4< T > operator*(const Matrix4< T >& m, const Vector4< T >& v)
{
	Vector4< T > out;
	out.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	out.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	out.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	out.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return out;
}

} // namespace Math
