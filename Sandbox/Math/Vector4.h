#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Vector4
{
	using Type = T;

	Type x, y, z, w;

	constexpr Vector4() = default;

	constexpr Vector4(const Vector4&) = default;

	constexpr Vector4(Vector4&&) = default;

	constexpr Vector4& operator=(const Vector4&) = default;

	constexpr Vector4& operator=(Vector4&&) = default;

	constexpr Vector4(Type x, Type y, Type z, Type w) noexcept
	    : x(x)
	    , y(y)
	    , z(z)
	    , w(w)
	{
	}

	constexpr Vector4(Type v) noexcept
	    : x(v)
	    , y(v)
	    , z(v)
	    , w(v)
	{
	}

	template< class X, class Y, class Z, class W >
	constexpr Vector4(X x, Y y, Z z, W w) noexcept
	    : x(static_cast< Type >(x))
	    , y(static_cast< Type >(y))
	    , z(static_cast< Type >(z))
	    , w(static_cast< Type >(w))
	{
	}

	template< class U >
	constexpr Vector4(const Vector4< U >& v) noexcept
	    : x(static_cast< Type >(v.x))
	    , y(static_cast< Type >(v.y))
	    , z(static_cast< Type >(v.z))
	    , w(static_cast< Type >(v.w))
	{
	}

	constexpr bool operator==(const Vector4& v) const noexcept
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	constexpr bool operator!=(const Vector4& v) const noexcept
	{
		return !(*this == v);
	}

	constexpr Vector4 operator+() const noexcept
	{
		return *this;
	}

	constexpr Vector4 operator-() const noexcept
	{
		return { -x, -y, -z, -w };
	}

	constexpr Vector4 operator+(const Vector4& v) const noexcept
	{
		return { x + v.x, y + v.y, z + v.z, w + v.w };
	}

	constexpr Vector4 operator-(const Vector4& v) const noexcept
	{
		return { x - v.x, y - v.y, z - v.z, w - v.w };
	}

	constexpr Vector4 operator*(const Vector4& v) const noexcept
	{
		return { x * v.x, y * v.y, z * v.z, w * v.w };
	}

	constexpr Vector4 operator/(const Vector4& v) const noexcept
	{
		return { x / v.x, y / v.y, z / v.z, w / v.w };
	}

	Vector4& operator+=(const Vector4& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vector4& operator*=(const Vector4& v) noexcept
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	Vector4& operator/=(const Vector4& v) noexcept
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	Vector4& operator=(const Type& v) noexcept
	{
		x = v;
		y = v;
		z = v;
		w = v;
		return *this;
	}

	Vector4& operator+=(const Type& v) noexcept
	{
		x += v;
		y += v;
		z += v;
		w += v;
		return *this;
	}

	Vector4& operator-=(const Type& v) noexcept
	{
		x -= v;
		y -= v;
		z -= v;
		w -= v;
		return *this;
	}

	Vector4& operator*=(const Type& v) noexcept
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
		return *this;
	}

	Vector4& operator/=(const Type& v) noexcept
	{
		x /= v;
		y /= v;
		z /= v;
		w /= v;
		return *this;
	}

	constexpr Vector3< T > xyz() const noexcept
	{
		return Vector3< T >(x, y, z);
	}
};

} // namespace Math
