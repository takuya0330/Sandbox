#pragma once

#include "Common.h"

class Ray
{
public:
	Ray() = default;

	Ray(const float3& origin, const float3& direction)
	    : m_origin(origin)
	    , m_direction(direction)
	{
	}

	float3 origin() const noexcept
	{
		return m_origin;
	}

	float3 direction() const noexcept
	{
		return m_direction;
	}

	float3 at(float t) const noexcept
	{
		return m_origin + m_direction * t;
	}

private:
	float3 m_origin;
	float3 m_direction;
};
