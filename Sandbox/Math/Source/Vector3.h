#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Vector3
{
	using Type = T;

	Type x, y, z;

	constexpr Vector3() = default;

	constexpr Vector3(const Vector3&) = default;

	constexpr Vector3(Vector3&&) = default;

	constexpr Vector3& operator=(const Vector3&) = default;

	constexpr Vector3& operator=(Vector3&&) = default;

	constexpr Vector3(Type x, Type y, Type z) noexcept
	    : x(x)
	    , y(y)
	    , z(z)
	{
	}

	constexpr Vector3(Type v) noexcept
	    : x(v)
	    , y(v)
	    , z(v)
	{
	}

	template< class X, class Y, class Z >
	constexpr Vector3(X x, Y y, Z z) noexcept
	    : x(static_cast< Type >(x))
	    , y(static_cast< Type >(y))
	    , z(static_cast< Type >(z))
	{
	}

	template< class U >
	constexpr Vector3(const Vector3< U >& v) noexcept
	    : x(static_cast< Type >(v.x))
	    , y(static_cast< Type >(v.y))
	    , z(static_cast< Type >(v.z))
	{
	}

	constexpr bool operator==(const Vector3& v) const noexcept
	{
		return x == v.x && y == v.y && z == v.z;
	}

	constexpr bool operator!=(const Vector3& v) const noexcept
	{
		return !(*this == v);
	}

	constexpr Vector3 operator+() const noexcept
	{
		return *this;
	}

	constexpr Vector3 operator-() const noexcept
	{
		return { -x, -y, -z };
	}

	constexpr Vector3 operator+(const Vector3& v) const noexcept
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	constexpr Vector3 operator-(const Vector3& v) const noexcept
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	constexpr Vector3 operator*(const Vector3& v) const noexcept
	{
		return { x * v.x, y * v.y, z * v.z };
	}

	constexpr Vector3 operator/(const Vector3& v) const noexcept
	{
		return { x / v.x, y / v.y, z / v.z };
	}

	Vector3& operator+=(const Vector3& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator*=(const Vector3& v) noexcept
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector3& operator/=(const Vector3& v) noexcept
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vector3& operator=(const Type& v) noexcept
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	Vector3& operator+=(const Type& v) noexcept
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	Vector3& operator-=(const Type& v) noexcept
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	Vector3& operator*=(const Type& v) noexcept
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vector3& operator/=(const Type& v) noexcept
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}
};

} // namespace Math
