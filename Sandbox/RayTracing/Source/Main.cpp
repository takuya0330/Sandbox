#include "Common.h"

#define RAYTRACING_OUTPUT_PPM (1)
#define RAYTRACING_OURPUT_STB (0)

#define RAYTRACING_01_OUTPUT_IMAGE        (0)
#define RAYTRACING_02_VECTOR              (0)
#define RAYTRACING_03_RAY                 (0)
#define RAYTRACING_04_HIT_SPHERE          (0)
#define RAYTRACING_05_HIT_SPHERE_NORMAL   (0)
#define RAYTRACING_06_HITTABLE            (0)
#define RAYTRACING_07_ANTI_ALIASING       (0)
#define RAYTRACING_08_DIFFUSE_MATERIAL    (0)
#define RAYTRACING_09_GAMMA               (0)
#define RAYTRACING_10_LAMBERT             (0)
#define RAYTRACING_11_HEMISPHERE          (0)
#define RAYTRACING_12_METAL_MATERIAL      (0)
#define RAYTRACING_13_METAL_MATERIAL_FUZZ (0)
#define RAYTRACING_14_DIELECTRIC_MATERIAL (0)
#define RAYTRACING_15_SCHLICK             (0)
#define RAYTRACING_16_CAMERA_FOV          (0)
#define RAYTRACING_17_CAMERA_FREE         (0)
#define RAYTRACING_18_DOF                 (0)
#define RAYTRACING_19_SCENE               (1)

namespace RayTracing {
namespace Util {

#if 0
#elif RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
void WriteColor(std::ostream& out, const Math::Color3F& color, int samples_per_pixel);
#elif RAYTRACING_02_VECTOR || RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL || RAYTRACING_06_HITTABLE
void WriteColor(std::ostream& out, const Math::Color3F& color);
#endif

#if 0
#elif RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world, int depth);
#elif RAYTRACING_06_HITTABLE || RAYTRACING_07_ANTI_ALIASING
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world);
#elif RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL
Math::Color3F GetRayColor(const Ray& ray);
#endif

#if 0
#elif RAYTRACING_05_HIT_SPHERE_NORMAL
float HitSphere(const Math::Float3& center, float radius, const Ray& ray);
#elif RAYTRACING_04_HIT_SPHERE
bool HitSphere(const Math::Float3& center, float radius, const Ray& ray);
#endif

#if 0
#elif RAYTRACING_19_SCENE
HittableList MakeRandomScene();
#endif

} // namespace Util
} // namespace RayTracing

int main(int, char**)
{
	using namespace RayTracing;

#if 0
#elif RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL || RAYTRACING_06_HITTABLE || RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
	constexpr float kAspectRatio = 16.0f / 9.0f;
	constexpr int   kImageWidth  = 320;
	constexpr int   kImageHeight = static_cast< int >(kImageWidth / kAspectRatio);
#elif RAYTRACING_01_OUTPUT_IMAGE || RAYTRACING_02_VECTOR
	constexpr int kImageWidth  = 256;
	constexpr int kImageHeight = 256;
#endif

#if 0
#elif RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
	constexpr int kSamplesPerPixel = 100;
#endif

#if 0
#elif RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
	constexpr int kMaxDepth = 50;
#endif

	std::string filename = "RayTracing";
#if 0
#elif RAYTRACING_19_SCENE
	filename += "19";
#elif RAYTRACING_18_DOF
	filename += "18";
#elif RAYTRACING_17_CAMERA_FREE
	filename += "17";
#elif RAYTRACING_16_CAMERA_FOV
	filename += "16";
#elif RAYTRACING_15_SCHLICK
	filename += "15";
#elif RAYTRACING_14_DIELECTRIC_MATERIAL
	filename += "14";
#elif RAYTRACING_13_METAL_MATERIAL_FUZZ
	filename += "13";
#elif RAYTRACING_12_METAL_MATERIAL
	filename += "12";
#elif RAYTRACING_11_HEMISPHERE
	filename += "11";
#elif RAYTRACING_10_LAMBERT
	filename += "10";
#elif RAYTRACING_09_GAMMA
	filename += "09";
#elif RAYTRACING_08_DIFFUSE_MATERIAL
	filename += "08";
#elif RAYTRACING_07_ANTI_ALIASING
	filename += "07";
#elif RAYTRACING_06_HITTABLE
	filename += "06";
#elif RAYTRACING_05_HIT_SPHERE_NORMAL
	filename += "05";
#elif RAYTRACING_04_HIT_SPHERE
	filename += "04";
#elif RAYTRACING_03_RAY
	filename += "03";
#elif RAYTRACING_02_VECTOR
	filename += "02";
#elif RAYTRACING_01_OUTPUT_IMAGE
	filename += "01";
#else
#error
#endif

#if RAYTRACING_OUTPUT_PPM
	filename += ".ppm";
#elif RAYTRACING_OUTPUT_STB
#endif

#if RAYTRACING_OUTPUT_PPM
	std::ofstream ofs(filename);

	ofs << "P3" << std::endl;
	ofs << kImageWidth << ' ' << kImageHeight << std::endl;
	ofs << "255" << std::endl;
#endif

#if 0
#elif RAYTRACING_19_SCENE
	Math::Float3 eye(13.0f, 2.0f, 3.0f);
	Math::Float3 focus(0.0f, 0.0f, 0.0f);
	Math::Float3 up(0.0f, 1.0f, 0.0f);
	float        focus_length = 10.0f;
	float        aperture     = 0.1f;

	Camera camera(eye, focus, up, kAspectRatio, 20.0f, aperture, focus_length);
#elif RAYTRACING_18_DOF
	Math::Float3 eye(3.0f, 3.0f, 2.0f);
	Math::Float3 focus(0.0f, 0.0f, -1.0f);
	Math::Float3 up(0.0f, 1.0f, 0.0f);
	float        focus_length = (eye - focus).Length();
	float        aperture     = 2.0f;

	Camera camera(eye, focus, up, kAspectRatio, 20.0f, aperture, focus_length);
#elif RAYTRACING_17_CAMERA_FREE
	Camera camera(Math::Float3(-2.0f, 2.0f, 1.0f), Math::Float3(0.0f, 0.0f, -1.0f), Math::Float3(0.0f, 1.0f, 0.0f), kAspectRatio, 20.0f);
#elif RAYTRACING_16_CAMERA_FOV
	Camera camera(kAspectRatio, 90.0f);
#elif RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK
	Camera camera(kAspectRatio);
#elif RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL || RAYTRACING_06_HITTABLE
	float viewport_height = 2.0f;
	float viewport_width  = kAspectRatio * viewport_height;
	float focal_length    = 1.0f;

	Math::Float3 origin(0, 0, 0);
	Math::Float3 horizontal(viewport_width, 0, 0);
	Math::Float3 vertical(0, viewport_height, 0);
	auto         lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - Math::Float3(0, 0, focal_length);
#endif

#if 0
#elif RAYTRACING_19_SCENE
	auto world = Util::MakeRandomScene();
#elif RAYTRACING_16_CAMERA_FOV
	float        R = std::cos(Math::kPI / 4);
	HittableList world;
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-R, 0.0f, -1.0f),
	    R,
	    std::make_shared< Lambertian >(Math::Color3F(0.0f, 0.0f, 1.0f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(R, 0.0f, -1.0f),
	    R,
	    std::make_shared< Lambertian >(Math::Color3F(1.0f, 0.0f, 0.0f))));
#elif RAYTRACING_15_SCHLICK || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF
	HittableList world;
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Lambertian >(Math::Color3F(0.7f, 0.3f, 0.3f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, -100.5f, -1.0f),
	    100.0f,
	    std::make_shared< Lambertian >(Math::Color3F(0.8f, 0.8f, 0.0f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.6f, 0.2f), 1.0f)));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Dielectric >(1.5f)));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-1.0f, 0.0f, -1.0f),
	    -0.45f,
	    std::make_shared< Dielectric >(1.5f)));
#elif RAYTRACING_14_DIELECTRIC_MATERIAL
	HittableList world;
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Lambertian >(Math::Color3F(0.7f, 0.3f, 0.3f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, -100.5f, -1.0f),
	    100.0f,
	    std::make_shared< Lambertian >(Math::Color3F(0.8f, 0.8f, 0.0f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.6f, 0.2f), 1.0f)));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Dielectric >(1.5f)));
#elif RAYTRACING_13_METAL_MATERIAL_FUZZ
	HittableList world;
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Lambertian >(Math::Color3F(0.7f, 0.3f, 0.3f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, -100.5f, -1.0f),
	    100.0f,
	    std::make_shared< Lambertian >(Math::Color3F(0.8f, 0.8f, 0.0f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.6f, 0.2f), 1.0f)));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.8f, 0.8f), 0.3f)));
#elif RAYTRACING_12_METAL_MATERIAL
	HittableList world;
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Lambertian >(Math::Color3F(0.7f, 0.3f, 0.3f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(0.0f, -100.5f, -1.0f),
	    100.0f,
	    std::make_shared< Lambertian >(Math::Color3F(0.8f, 0.8f, 0.0f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.6f, 0.2f))));
	world.Add(std::make_shared< Sphere >(
	    Math::Float3(-1.0f, 0.0f, -1.0f),
	    0.5f,
	    std::make_shared< Metal >(Math::Color3F(0.8f, 0.8f, 0.8f))));
#elif RAYTRACING_06_HITTABLE || RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE
	HittableList world;
	world.Add(std::make_shared< Sphere >(Math::Float3(0.0f, 0.0f, -1.0f), 0.5f));
	world.Add(std::make_shared< Sphere >(Math::Float3(0.0f, -100.5f, -1.0f), 100.0f));
#endif

	for (int y = kImageHeight - 1; y >= 0; --y)
	{
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for (int x = 0; x < kImageWidth; ++x)
		{
#if 0
#elif RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
			Math::Color3F pixel_color(0, 0, 0);
			for (int i = 0; i < kSamplesPerPixel; ++i)
			{
				auto u = (x + Util::Random(0.0f, 1.0f)) / (kImageWidth - 1);
				auto v = (y + Util::Random(0.0f, 1.0f)) / (kImageHeight - 1);
				auto r = camera.GetRay(u, v);
				pixel_color += Util::GetRayColor(r, world, kMaxDepth);
			}
			Util::WriteColor(ofs, pixel_color, kSamplesPerPixel);
#elif RAYTRACING_07_ANTI_ALIASING
			Math::Color3F pixel_color(0, 0, 0);
			for (int i = 0; i < kSamplesPerPixel; ++i)
			{
				auto u = (x + Util::Random(0.0f, 1.0f)) / (kImageWidth - 1);
				auto v = (y + Util::Random(0.0f, 1.0f)) / (kImageHeight - 1);
				auto r = camera.GetRay(u, v);
				pixel_color += Util::GetRayColor(r, world);
			}
			Util::WriteColor(ofs, pixel_color, kSamplesPerPixel);
#elif RAYTRACING_06_HITTABLE
			auto u = static_cast< float >(x) / (kImageWidth - 1);
			auto v = static_cast< float >(y) / (kImageHeight - 1);
			Ray  r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Util::WriteColor(ofs, Util::GetRayColor(r, world));
#elif RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL
			auto u = static_cast< float >(x) / (kImageWidth - 1);
			auto v = static_cast< float >(y) / (kImageHeight - 1);
			Ray  r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Util::WriteColor(ofs, Util::GetRayColor(r));
#elif RAYTRACING_02_VECTOR
			Math::Color3F pixel_color(
			    static_cast< float >(x) / (kImageWidth - 1),
			    static_cast< float >(y) / (kImageHeight - 1),
			    0.25f);
			Util::WriteColor(ofs, pixel_color);
#elif RAYTRACING_01_OUTPUT_IMAGE
			auto r = static_cast< float >(x) / (kImageWidth - 1);
			auto g = static_cast< float >(y) / (kImageHeight - 1);
			auto b = 0.25f;

			int ir = static_cast< int >(255 * r);
			int ig = static_cast< int >(255 * g);
			int ib = static_cast< int >(255 * b);

			ofs << ir << ' ' << ig << ' ' << ib << std::endl;
#else
#error
#endif
		}
	}

	return 0;
}

namespace RayTracing {
namespace Util {

#if 0
#elif RAYTRACING_09_GAMMA || RAYTRACING_10_LAMBERT || RAYTRACING_11_HEMISPHERE || RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
void WriteColor(std::ostream& out, const Math::Color3F& color, int samples_per_pixel)
{
	auto scale = 1.0f / samples_per_pixel;
	auto r     = std::clamp(std::sqrt(color.x * scale), 0.0f, 1.0f);
	auto g     = std::clamp(std::sqrt(color.y * scale), 0.0f, 1.0f);
	auto b     = std::clamp(std::sqrt(color.z * scale), 0.0f, 1.0f);

	Math::Vec3< int > c(
	    static_cast< int >(255 * r),
	    static_cast< int >(255 * g),
	    static_cast< int >(255 * b));

	out << c << std::endl;
}
#elif RAYTRACING_07_ANTI_ALIASING || RAYTRACING_08_DIFFUSE_MATERIAL
void WriteColor(std::ostream& out, const Math::Color3F& color, int samples_per_pixel)
{
	auto scale = 1.0f / samples_per_pixel;
	auto r     = std::clamp(color.x * scale, 0.0f, 1.0f);
	auto g     = std::clamp(color.y * scale, 0.0f, 1.0f);
	auto b     = std::clamp(color.z * scale, 0.0f, 1.0f);

	Math::Vec3< int > c(
	    static_cast< int >(255 * r),
	    static_cast< int >(255 * g),
	    static_cast< int >(255 * b));

	out << c << std::endl;
}
#elif RAYTRACING_02_VECTOR || RAYTRACING_03_RAY || RAYTRACING_04_HIT_SPHERE || RAYTRACING_05_HIT_SPHERE_NORMAL || RAYTRACING_06_HITTABLE
void WriteColor(std::ostream& out, const Math::Color3F& color)
{
	Math::Vec3< int > c(
	    static_cast< int >(255 * color.x),
	    static_cast< int >(255 * color.y),
	    static_cast< int >(255 * color.z));

	out << c << std::endl;
}
#endif

#if 0
#elif RAYTRACING_12_METAL_MATERIAL || RAYTRACING_13_METAL_MATERIAL_FUZZ || RAYTRACING_14_DIELECTRIC_MATERIAL || RAYTRACING_15_SCHLICK || RAYTRACING_16_CAMERA_FOV || RAYTRACING_17_CAMERA_FREE || RAYTRACING_18_DOF || RAYTRACING_19_SCENE
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world, int depth)
{
	if (depth <= 0)
		return Math::Color3F(0, 0, 0);

	HitRecord rec;
	if (world.Hit(ray, 0.001f, Math::kInfinity, rec))
	{
		Ray           scattered;
		Math::Color3F attenuation;
		if (rec.m->Scatter(ray, rec, attenuation, scattered))
		{
			return attenuation * GetRayColor(scattered, world, depth - 1);
		}
		return Math::Color3F(0, 0, 0);
	}

	Math::Float3 ndir = Math::Normalize(ray.GetDirection());
	float        t    = 0.5f * (ndir.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_11_HEMISPHERE
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world, int depth)
{
	if (depth <= 0)
		return Math::Color3F(0, 0, 0);

	HitRecord rec;
	if (world.Hit(ray, 0.001f, kInfinity, rec))
	{
		auto target = rec.p + RandomInHemisphere(rec.n);
		return 0.5f * GetRayColor(Ray(rec.p, target - rec.p), world, depth - 1);
	}

	Math::Float3 ndir = Math::Normalize(ray.GetDirection());
	float        t    = 0.5f * (ndir.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_10_LAMBERT
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world, int depth)
{
	if (depth <= 0)
		return Math::Color3F(0, 0, 0);

	HitRecord rec;
	if (world.Hit(ray, 0.001f, kInfinity, rec))
	{
		auto target = rec.p + rec.n + RandomUnitF3();
		return 0.5f * GetRayColor(Ray(rec.p, target - rec.p), world, depth - 1);
	}

	Math::Float3 ndir = Math::Normalize(ray.GetDirection());
	float        t    = 0.5f * (ndir.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_08_DIFFUSE_MATERIAL || RAYTRACING_09_GAMMA
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world, int depth)
{
	if (depth <= 0)
		return Math::Color3F(0, 0, 0);

	HitRecord rec;
	if (world.Hit(ray, 0, kInfinity, rec))
	{
		auto target = rec.p + rec.n + RandomInUnitSphere();
		return 0.5f * GetRayColor(Ray(rec.p, target - rec.p), world, depth - 1);
	}

	Math::Float3 ndir = Math::Normalize(ray.GetDirection());
	float        t    = 0.5f * (ndir.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_06_HITTABLE || RAYTRACING_07_ANTI_ALIASING
Math::Color3F GetRayColor(const Ray& ray, const IHittable& world)
{
	HitRecord rec;
	if (world.Hit(ray, 0, kInfinity, rec))
	{
		return 0.5f * (rec.n + Math::Color3F(1.0f, 1.0f, 1.0f));
	}

	Math::Float3 ndir = Math::Normalize(ray.GetDirection());
	float        t    = 0.5f * (ndir.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_05_HIT_SPHERE_NORMAL
Math::Color3F GetRayColor(const Ray& ray)
{
	Math::Color3F sphere_pos(0.0f, 0.0f, -1.0f);
	float         sphere_rad = 0.5f;

	if (auto t = HitSphere(sphere_pos, sphere_rad, ray); t > 0.0f)
	{
		auto n = Math::Normalize(ray.At(t) - sphere_pos);
		return 0.5f * Math::Color3F(n.x + 1.0f, n.y + 1.0f, n.z + 1.0f);
	}

	Math::Float3 nd = Math::Normalize(ray.GetDirection());
	float        t  = 0.5f * (nd.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_04_HIT_SPHERE
Math::Color3F GetRayColor(const Ray& ray)
{
	Math::Color3F sphere_pos(0.0f, 0.0f, -1.0f);
	float         sphere_rad = 0.5f;

	if (HitSphere(sphere_pos, sphere_rad, ray))
		return Math::Color3F(1.0f, 0.0f, 0.0f);

	Math::Float3 nd = Math::Normalize(ray.GetDirection());
	float        t  = 0.5f * (nd.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#elif RAYTRACING_03_RAY
Math::Color3F GetRayColor(const Ray& ray)
{
	Math::Float3 nd = Math::Normalize(ray.GetDirection());
	float        t  = 0.5f * (nd.y + 1.0f);
	return (1.0f - t) * Math::Color3F(1.0f, 1.0f, 1.0f) + t * Math::Color3F(0.5f, 0.7f, 1.0f);
}
#endif

#if 0
#elif RAYTRACING_05_HIT_SPHERE_NORMAL
float HitSphere(const Math::Float3& center, float radius, const Ray& ray)
{
	auto oc = ray.GetOrigin() - center;
	auto a  = Math::Dot(ray.GetDirection(), ray.GetDirection());
	auto b  = 2.0f * Math::Dot(oc, ray.GetDirection());
	auto c  = Math::Dot(oc, oc) - radius * radius;
	auto d  = b * b - 4 * a * c;
	return (d > 0.0f) ? (-b - std::sqrt(d)) / (2.0f * a) : -1.0f;
}
#elif RAYTRACING_04_HIT_SPHERE
bool HitSphere(const Math::Float3& center, float radius, const Ray& ray)
{
	auto oc = ray.GetOrigin() - center;
	auto a  = Math::Dot(ray.GetDirection(), ray.GetDirection());
	auto b  = 2.0f * Math::Dot(oc, ray.GetDirection());
	auto c  = Math::Dot(oc, oc) - radius * radius;
	return (b * b - 4 * a * c) > 0.0f;
}
#endif

#if 0
#elif RAYTRACING_19_SCENE
HittableList MakeRandomScene()
{
	HittableList world;

	auto ground_material = std::make_shared< Lambertian >(Math::Color3F(0.5f, 0.5f, 0.5f));
	world.Add(std::make_shared< Sphere >(Math::Float3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material));

    auto random_color = [](float min, float max) {
		return Math::Color3F(
		    Util::Random(min, max),
		    Util::Random(min, max),
		    Util::Random(min, max));
	};

	for (int i = -11; i < 11; ++i)
	{
		for (int j = -11; j < 11; ++j)
		{
			auto         choose_mat = Util::Random(0.0f, 1.0f);
			Math::Float3 center(i + 0.9f * Util::Random(0.0f, 1.0f), 0.2f, j + 0.9f * Util::Random(0.0f, 1.0f));

			if ((center - Math::Float3(4.0f, 0.2f, 0.0f)).Length() > 0.9f)
			{
				std::shared_ptr< IMaterial > sphere_material;
                if (choose_mat < 0.8f)
                {
					auto albedo = random_color(0.0f, 1.0f) * random_color(0.0f, 1.0f);
					sphere_material = std::make_shared< Lambertian >(albedo);
					world.Add(std::make_shared< Sphere >(center, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95f)
                {
					auto albedo = random_color(0.5f, 1.0f);
					auto fuzz   = Util::Random(0.0f, 0.5f);
					sphere_material = std::make_shared< Metal >(albedo, fuzz);
					world.Add(std::make_shared< Sphere >(center, 0.2f, sphere_material));
                }
                else
                {
					sphere_material = std::make_shared< Dielectric >(1.5f);
					world.Add(std::make_shared< Sphere >(center, 0.2f, sphere_material));
				}
			}
		}
	}

    auto material1 = std::make_shared< Dielectric >(1.5f);
	world.Add(std::make_shared< Sphere >(Math::Float3(0.0f, 1.0f, 0.0f), 1.0f, material1));
	auto material2 = std::make_shared< Lambertian >(Math::Color3F(0.4f, 0.2f, 0.1f));
	world.Add(std::make_shared< Sphere >(Math::Float3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
	auto material3 = std::make_shared< Metal >(Math::Color3F(0.7f, 0.6f, 0.5f), 0.0f);
	world.Add(std::make_shared< Sphere >(Math::Float3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    return world;
}
#endif

} // namespace Util
} // namespace RayTracing
