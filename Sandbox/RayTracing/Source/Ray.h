#pragma once

#include "Vec3.h"

namespace RayTracing {

class Ray
{
public:
	Ray() = default;

	Ray(const Math::Float3& origin, const Math::Float3& direction)
	    : m_origin(origin)
	    , m_direction(direction)
	{
	}

	Math::Float3 GetOrigin() const noexcept
	{
		return m_origin;
	}

	Math::Float3 GetDirection() const noexcept
	{
		return m_direction;
	}

	Math::Float3 At(float t) const noexcept
	{
		return m_origin + m_direction * t;
	}

private:
	Math::Float3 m_origin;
	Math::Float3 m_direction;
};

} // namespace RayTracing
