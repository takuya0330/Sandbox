#pragma once

#include "Ray.h"

namespace RayTracing {

class Camera
{
public:
	Camera(
	    const Math::Float3& eye,
	    const Math::Float3& focus,
	    const Math::Float3& up,
	    float               aspect_ratio,
	    float               fov,
	    float               aperture,
	    float               focus_length)
	    : m_origin(eye)
	    , m_lower_left_corner()
	    , m_horizontal()
	    , m_vertical()
	    , m_lens_radius()
	{
		float theta           = (fov * Math::kPI) / 180;
		float h               = std::tan(theta / 2);
		float viewport_height = 2.0f * h;
		float viewport_width  = viewport_height * aspect_ratio;

		auto w = Math::Normalize(eye - focus);
		auto u = Math::Normalize(Math::Cross(up, w));
		auto v = Math::Cross(w, u);

		m_horizontal        = focus_length * viewport_width * u;
		m_vertical          = focus_length * viewport_height * v;
		m_lower_left_corner = m_origin - m_horizontal / 2.0f - m_vertical / 2.0f - w * focus_length;

        m_lens_radius = aperture / 2;
	}

	Ray GetRay(float u, float v) const
	{
		auto rd = m_lens_radius * Math::RandomInUnitDisk();
		auto offset = u * rd.x + v * rd.y;
		return Ray(m_origin + offset, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin - offset);
	}

private:
	Math::Float3 m_origin;
	Math::Float3 m_lower_left_corner;
	Math::Float3 m_horizontal;
	Math::Float3 m_vertical;
	float        m_lens_radius;
};

} // namespace RayTracing
