#include "Hittable.h"
#include "Material.h"

namespace RayTracing {

Sphere::Sphere(const Math::Float3& c, float r, std::shared_ptr< IMaterial > m)
    : m_center(c)
    , m_radius(r)
    , m_material(m)
{
}

bool Sphere::Hit(const Ray& r, float min, float max, HitRecord& rec) const
{
	auto oc = r.GetOrigin() - m_center;
	auto a  = r.GetDirection().LengthSq();
	auto b  = Math::Dot(oc, r.GetDirection());
	auto c  = oc.LengthSq() - m_radius * m_radius;
	auto d  = b * b - a * c;

	if (d > 0.0f)
	{
		auto root = std::sqrt(d);
		auto temp = (-b - root) / a;
		if (min < temp && temp < max)
		{
			rec.t = temp;
			rec.p = r.At(rec.t);
			rec.SetFaceNormal(r, (rec.p - m_center) / m_radius);
			rec.m = m_material;
			return true;
		}
		temp = (-b + root) / a;
		if (min < temp && temp < max)
		{
			rec.t = temp;
			rec.p = r.At(rec.t);
			rec.SetFaceNormal(r, (rec.p - m_center) / m_radius);
			rec.m = m_material;
			return true;
		}
	}

	return false;
}

bool HittableList::Hit(const Ray& r, float min, float max, HitRecord& rec) const
{
	HitRecord temp;
	bool      is_hit_any     = false;
	float     closest_so_far = max;

    for (const auto& it : m_objects)
    {
		if (it->Hit(r, min, closest_so_far, temp))
		{
			is_hit_any     = true;
			closest_so_far = temp.t;
			rec            = temp;
		}
    }

    return is_hit_any;
}

} // namespace RayTracing
