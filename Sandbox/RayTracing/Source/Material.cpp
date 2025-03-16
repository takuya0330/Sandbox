#include "Material.h"

namespace RayTracing {
namespace {

float Schlick(float cosine, float ref_idx)
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0      = r0 * r0;
	return r0 + (1 - r0) * powf((1 - cosine), 5);
}

} // namespace

bool Lambertian::Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const
{
	auto scatter_direction = rec.n + Math::RandomUnitF3();
	scattered              = Ray(rec.p, scatter_direction);
	attenuation            = m_albedo;
	return true;
}

bool Metal::Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const
{
	auto reflected = Math::Reflect(Math::Normalize(ray.GetDirection()), rec.n);
	scattered      = Ray(rec.p, reflected + m_fuzz * Math::RandomInUnitSphere());
	attenuation    = m_albedo;
	return Math::Dot(scattered.GetDirection(), rec.n) > 0.0f;
}

bool Dielectric::Scatter(const Ray& ray, const HitRecord& rec, Math::Color3F& attenuation, Ray& scattered) const
{
	attenuation          = Math::Color3F(1.0f, 1.0f, 1.0f);
	float etai_over_etat = rec.front_face ? 1.0f / m_ref_idx : m_ref_idx;

	auto  nd        = Math::Normalize(ray.GetDirection());
	float cos_theta = std::min(Math::Dot(-nd, rec.n), 1.0f);
	float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);
	if (etai_over_etat * sin_theta > 1.0f)
	{
		auto reflected = Math::Reflect(nd, rec.n);
		scattered      = Ray(rec.p, reflected);
		return true;
	}

    auto reflect_prob = Schlick(cos_theta, etai_over_etat);
    if (Util::Random(0.0f, 1.0f) < reflect_prob)
    {
		auto reflected = Math::Reflect(nd, rec.n);
		scattered      = Ray(rec.p, reflected);
		return true;
    }

	auto refracted = Math::Refract(nd, rec.n, etai_over_etat);
	scattered      = Ray(rec.p, refracted);
	return true;
}

} // namespace RayTracing
