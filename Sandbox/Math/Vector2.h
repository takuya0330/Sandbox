#pragma once

#include "Types.h"

namespace Math {

template< class T >
struct Vector2
{
	using Type = T;

	Type x, y;

	constexpr Vector2() = default;

	constexpr Vector2(const Vector2&) = default;

	constexpr Vector2(Vector2&&) = default;

	constexpr Vector2& operator=(const Vector2&) = default;

	constexpr Vector2& operator=(Vector2&&) = default;

	constexpr Vector2(Type x, Type y) noexcept
	    : x(x)
	    , y(y)
	{
	}

	constexpr Vector2(Type v) noexcept
	    : x(v)
	    , y(v)
	{
	}

	template< class X, class Y >
	constexpr Vector2(X x, Y y) noexcept
	    : x(static_cast< Type >(x))
	    , y(static_cast< Type >(y))
	{
	}

	template< class U >
	constexpr Vector2(const Vector2< U >& v) noexcept
	    : x(static_cast< Type >(v.x))
	    , y(static_cast< Type >(v.y))
	{
	}

	constexpr bool operator==(const Vector2& v) const noexcept
	{
		return x == v.x && y == v.y;
	}

	constexpr bool operator!=(const Vector2& v) const noexcept
	{
		return !(*this == v);
	}

	constexpr Vector2 operator+() const noexcept
	{
		return *this;
	}

	constexpr Vector2 operator-() const noexcept
	{
		return { -x, -y };
	}

	constexpr Vector2 operator+(const Vector2& v) const noexcept
	{
		return { x + v.x, y + v.y };
	}

	constexpr Vector2 operator-(const Vector2& v) const noexcept
	{
		return { x - v.x, y - v.y };
	}

	constexpr Vector2 operator*(const Vector2& v) const noexcept
	{
		return { x * v.x, y * v.y };
	}

	constexpr Vector2 operator/(const Vector2& v) const noexcept
	{
		return { x / v.x, y / v.y };
	}

	Vector2& operator+=(const Vector2& v) noexcept
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& operator*=(const Vector2& v) noexcept
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2& operator/=(const Vector2& v) noexcept
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vector2& operator=(const Type& v) noexcept
	{
		x = v;
		y = v;
		return *this;
	}

	Vector2& operator+=(const Type& v) noexcept
	{
		x += v;
		y += v;
		return *this;
	}

	Vector2& operator-=(const Type& v) noexcept
	{
		x -= v;
		y -= v;
		return *this;
	}

	Vector2& operator*=(const Type& v) noexcept
	{
		x *= v;
		y *= v;
		return *this;
	}

	Vector2& operator/=(const Type& v) noexcept
	{
		x /= v;
		y /= v;
		return *this;
	}
};

} // namespace Math
