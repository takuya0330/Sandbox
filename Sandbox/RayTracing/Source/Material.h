#pragma once

#include "Hittable.h"

namespace RayTracing {

class IMaterial
{
public:
	virtual ~IMaterial() = default;

	virtual bool Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public IMaterial
{
public:
	Lambertian(const Math::Color3F& color)
	    : m_albedo(color)
	{
	}

    bool Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const override;

private:
	Math::Color3F m_albedo;
};

class Metal : public IMaterial
{
public:
	Metal(const Math::Color3F& color, float fuzz)
	    : m_albedo(color)
	    , m_fuzz(fuzz)
	{
	}

	bool Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const override;

private:
	Math::Color3F m_albedo;
	float         m_fuzz;
};

class Dielectric : public IMaterial
{
public:
	Dielectric(float ri)
	    : m_ref_idx(ri)
	{
	}

    bool Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const override;

private:
	float m_ref_idx;
};

} // namespace RayTracing
