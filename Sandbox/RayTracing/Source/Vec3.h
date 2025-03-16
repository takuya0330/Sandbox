#pragma once

#include <cmath>

#include "Random.h"

namespace RayTracing {
namespace Math {

constexpr float kInfinity = std::numeric_limits< float >::max();
constexpr float kPI       = 3.1415926535897932385f;

template< typename T >
struct Vec3
{
	T x, y, z;

	Vec3()
	    : x()
	    , y()
	    , z()
	{
	}

	Vec3(T x, T y, T z)
	    : x(x)
	    , y(y)
	    , z(z)
	{
	}

	Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}

	Vec3& operator+=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3& operator*=(const T v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vec3& operator/=(const T v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	T LengthSq() const
	{
		return x * x + y * y + z * z;
	}

	T Length() const
	{
		return std::sqrt(LengthSq());
	}
};

template< typename T >
inline Vec3< T > operator+(const Vec3< T >& a, const Vec3< T >& b)
{
	return Vec3< T >(a.x + b.x, a.y + b.y, a.z + b.z);
}

template< typename T >
inline Vec3< T > operator+(const Vec3< T >& a, const T b)
{
	return Vec3< T >(a.x + b, a.y + b, a.z + b);
}

template< typename T >
inline Vec3< T > operator-(const Vec3< T >& a, const Vec3< T >& b)
{
	return Vec3< T >(a.x - b.x, a.y - b.y, a.z - b.z);
}

template< typename T >
inline Vec3< T > operator-(const Vec3< T >& a, const T b)
{
	return Vec3< T >(a.x - b, a.y - b, a.z - b);
}

template< typename T >
inline Vec3< T > operator*(const Vec3< T >& a, const Vec3< T >& b)
{
	return Vec3< T >(a.x * b.x, a.y * b.y, a.z * b.z);
}

template< typename T >
inline Vec3< T > operator*(const Vec3< T >& v, const T t)
{
	return Vec3< T >(v.x * t, v.y * t, v.z * t);
}

template< typename T >
inline Vec3< T > operator*(const T t, const Vec3< T >& v)
{
	return v * t;
}

template< typename T >
inline Vec3< T > operator/(const Vec3< T >& v, const T t)
{
	return v * (static_cast< T >(1) / t);
}

template< typename T >
inline T Dot(const Vec3< T >& a, const Vec3< T >& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template< typename T >
inline Vec3< T > Cross(const Vec3< T >& a, const Vec3< T >& b)
{
	return Vec3< T >(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template< typename T >
inline Vec3< T > Normalize(const Vec3< T >& v)
{
	return v / v.Length();
}

using Float3  = Vec3< float >;
using Point3F = Vec3< float >;
using Color3F = Vec3< float >;

inline Float3 RandomInUnitSphere()
{
	while (true)
	{
		Float3 p(Util::Random(-1.0f, 1.0f), Util::Random(-1.0f, 1.0f), Util::Random(-1.0f, 1.0f));
		if (p.LengthSq() >= 1)
			continue;
		return p;
	}
}

inline Float3 RandomInUnitDisk()
{
	while (true)
	{
		Float3 p(Util::Random(-1.0f, 1.0f), Util::Random(-1.0f, 1.0f), 0.0f);
		if (p.LengthSq() >= 1)
			continue;
		return p;
	}
}

inline Float3 RandomUnitF3()
{
	auto a = Util::Random(0.0f, 2 * kPI);
	auto z = Util::Random(-1.0f, 1.0f);
	auto r = std::sqrt(1 - z * z);
	return Float3(r * std::cos(a), r * std::sin(a), z);
}

inline Float3 RandomInHemisphere(const Float3& n)
{
	auto unit_sphere = RandomInUnitSphere();
	if (Dot(unit_sphere, n) > 0.0f)
		return unit_sphere;
	else
		return -unit_sphere;
}

inline Float3 Reflect(const Float3& v, const Float3& n)
{
	return v - 2 * Dot(v, n) * n;
}

inline Float3 Refract(const Float3& v, const Float3& n, float etai_over_etat)
{
	auto cos_theta = Dot(-v, n);
	auto r_out_parallel = etai_over_etat * (v + cos_theta * n);
	auto r_out_perp     = -std::sqrt(1.0f - r_out_parallel.LengthSq()) * n;
	return r_out_parallel + r_out_perp;
}

} // namespace Math
} // namespace RayTracing
