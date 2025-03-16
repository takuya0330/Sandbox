#pragma once

#include <memory>
#include <vector>

#include "Ray.h"

namespace RayTracing {

class IMaterial;

struct HitRecord
{
	Math::Float3                 p;
	Math::Float3                 n;
	std::shared_ptr< IMaterial > m;
	float                        t;
	bool                         front_face;

	inline void SetFaceNormal(const Ray& r, const Math::Float3& outward_normal)
	{
		front_face = Math::Dot(r.GetDirection(), outward_normal) < 0.0f;
		n          = front_face ? outward_normal : -outward_normal;
	}
};

class IHittable
{
public:
	virtual ~IHittable() = default;

	virtual bool Hit(const Ray& r, float min, float max, HitRecord& rec) const = 0;
};

class Sphere : public IHittable
{
public:
	Sphere(const Math::Float3& c, float r, std::shared_ptr< IMaterial > m);

	bool Hit(const Ray& r, float min, float max, HitRecord& rec) const override;

private:
	Math::Float3                 m_center;
	float                        m_radius;
	std::shared_ptr< IMaterial > m_material;
};

class HittableList : public IHittable
{
public:
	HittableList() = default;

	HittableList(std::shared_ptr< IHittable > obj)
	{
		Add(obj);
	}

	void Add(std::shared_ptr< IHittable > obj)
	{
		m_objects.emplace_back(obj);
	}

	void Clear()
	{
		m_objects.clear();
	}

	bool Hit(const Ray& r, float min, float max, HitRecord& rec) const override;

private:
	std::vector< std::shared_ptr< IHittable > > m_objects;
};

} // namespace RayTracing
