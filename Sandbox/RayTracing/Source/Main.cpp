#include <fstream>
#include <iostream>

#include "Ray.h"

inline std::ostream& operator<<(std::ostream& out, const float3& v)
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

void   write(std::ofstream& ofs, const int width, const int height);
void   write_color(std::ofstream& ofs, const float3& color);
float3 ray_color(const Ray& ray);
bool   hit_sphere(const float3& center, float radius, const Ray& r);

int main(int, char**)
{
#if 0
#elif RAYTRACING_04_HIT_SPHERE
	std::ofstream ofs("RayTracing04.ppm");
	write(ofs, 384, 0);
#elif RAYTRACING_03_RAY
	std::ofstream ofs("RayTracing03.ppm");
	write(ofs, 384, 0);
#elif RAYTRACING_02_VECTOR
	std::ofstream ofs("RayTracing02.ppm");
	write(ofs, 256, 256);
#elif RAYTRACING_01_OUTPUT_PPM
	std::ofstream ofs("RayTracing01.ppm");
	write(ofs, 256, 256);
#endif

	return 0;
}

void write(std::ofstream& ofs, const int width, const int height)
{
	int2 size(width, height);

#if 0
#elif RAYTRACING_04_HIT_SPHERE
	const auto aspect_ratio = 16.0f / 9.0f;
	size.y                  = static_cast< int >(size.x / aspect_ratio);

	auto cpos  = float3(0, 0, 3);
	auto focus = float3(0, 0, 0);
	auto up    = float3(0, 1, 0);
#if RAYTRACING_USING_MATH_DXM
	auto view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&cpos), DirectX::XMLoadFloat3(&focus), DirectX::XMLoadFloat3(&up));
	auto proj = DirectX::XMMatrixPerspectiveLH(45.0f, aspect_ratio, 0.1f, 100.0f);
	auto ivp  = DirectX::XMMatrixInverse(nullptr, view * proj);
#elif RAYTRACING_USING_MATH_MATH
	auto view = Math::LookAtLH(cpos, focus, up);
	auto proj = Math::PerspectiveFovLH(45.0f, aspect_ratio, 0.1f, 100.0f);
	auto ivp  = Math::Inverse(Math::Mul(view, proj));
#endif
#elif RAYTRACING_03_RAY
	const auto aspect_ratio = 16.0 / 9.0;
	size.y                  = static_cast< int >(size.x / aspect_ratio);

	auto viewport_height = 2.0;
	auto viewport_width  = aspect_ratio * viewport_height;
	auto focal_length    = 1.0;

	auto origin            = float3(0, 0, 3);
	auto horizontal        = float3(viewport_width, 0, 0);
	auto vertical          = float3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - float3(0, 0, focal_length);
#endif

	ofs << "P3" << std::endl;
	ofs << size.x << ' ' << size.y << std::endl;
	ofs << "255" << std::endl;

	for (int y = size.y - 1; y >= 0; --y)
	{
		std::cerr << "\rScanlines remaing: " << y << ' ' << std::flush;
		for (int x = 0; x < size.x; ++x)
		{
#if 0
#elif RAYTRACING_04_HIT_SPHERE
			float2 uv = float2(x / size.x, y / size.y) * 2.0f - 1.0f;
			uv.y *= -1;
#if RAYTRACING_USING_MATH_DXM
			auto dir = float4(uv.x, uv.y, 0, 1) * ivp;
			dir.x /= dir.w;
			dir.y /= dir.w;
			dir.z /= dir.w;
			auto fd = float3(dir.x - cpos.x, dir.y - cpos.y, dir.z - cpos.z);
			auto vd = DirectX::XMLoadFloat3(&fd);
			auto vn = DirectX::XMVector3Normalize(vd);
			float3 fn(0, 0, 0);
			DirectX::XMStoreFloat3(&fn, vn);
			Ray  r(cpos, fn);
#elif RAYTRACING_USING_MATH_MATH
			auto dir = float4(uv.x, uv.y, 0, 1) * ivp;
			dir.xyz() /= dir.w;
			Ray r(cpos, Math::Normalize(dir.xyz() - cpos));
#endif
			float3 color = ray_color(r);
			write_color(ofs, color);
#elif RAYTRACING_03_RAY
			auto   u = double(x) / (size.x - 1);
			auto   v = double(y) / (size.y - 1);
			Ray    r(origin, lower_left_corner + horizontal * u + vertical * v - origin);
			float3 color = ray_color(r);
			write_color(ofs, color);
#elif RAYTRACING_02_VECTOR
			float3 color(double(x) / (width - 1), double(y) / (height - 1), 0.25);
			write_color(ofs, color);
#elif RAYTRACING_01_OUTPUT_PPM
			auto r = double(x) / (width - 1);
			auto g = double(y) / (height - 1);
			auto b = 0.25;

			int ir = static_cast< int >(255.999 * r);
			int ig = static_cast< int >(255.999 * g);
			int ib = static_cast< int >(255.999 * b);

			ofs << ir << ' ' << ig << ' ' << ib << '\n';
#endif
		}
	}
	std::cerr << std::endl;
	std::cerr << "Done." << std::endl;
}

void write_color(std::ofstream& ofs, const float3& color)
{
	// clang-format off
	ofs << static_cast<int>(255.999 * color.x) << ' '
        << static_cast<int>(255.999 * color.y) << ' '
        << static_cast<int>(255.999 * color.z) << '\n';
	// clang-format on
}

float3 ray_color(const Ray& ray)
{
#if 0
#elif RAYTRACING_04_HIT_SPHERE
	if (hit_sphere(float3(0, 0, 0), 1.0f, ray))
		return float3(1, 0, 0);
	auto t = 0.5f * (ray.direction().y + 1.0f);
	return float3(1, 1, 1) * (1.0f - t) + float3(0.5f, 0.7f, 1.0f) * t;
#elif RAYTRACING_03_RAY
#if RAYTRACING_USING_MATH_DXM
	auto   fd = ray.direction();
	auto   vd = DirectX::XMLoadFloat3(&fd);
	auto   vn = DirectX::XMVector3Normalize(vd);
	float3 dir(0, 0, 0);
	DirectX::XMStoreFloat3(&dir, vn);
#elif RAYTRACING_USING_MATH_MATH
	auto dir = Math::Normalize(ray.direction());
#endif
	auto t = 0.5f * (dir.y + 1.0f);
	return float3(1, 1, 1) * (1.0f - t) + float3(0.5f, 0.7f, 1.0f) * t;
#else
	return float3(0, 0, 0);
#endif
}

bool hit_sphere(const float3& center, float radius, const Ray& r)
{
	auto oc = r.origin() - center;
#if RAYTRACING_USING_MATH_DXM
	auto fd = r.direction();
	auto vd = DirectX::XMLoadFloat3(&fd);
	auto vo = DirectX::XMLoadFloat3(&oc);
	auto a  = DirectX::XMVector3Dot(vd, vd);
	auto b  = DirectX::XMVectorMultiply(DirectX::XMVectorSet(2.0f, 2.0f, 2.0f, 2.0f), DirectX::XMVector3Dot(vo, vd));
	auto r2 = radius * radius;
	auto c  = DirectX::XMVectorSubtract(DirectX::XMVector3Dot(vo, vo), DirectX::XMLoadFloat(&r2));
	auto d  = DirectX::XMVectorSubtract(DirectX::XMVectorMultiply(b, b), DirectX::XMVectorMultiply(DirectX::XMVectorMultiply(DirectX::XMVectorSet(4.0f, 4.0f, 4.0f, 4.0f), a), c));
	return DirectX::XMVector3Equal(d, DirectX::XMVectorSet(0, 0, 0, 0));
#elif RAYTRACING_USING_MATH_MATH
	auto a = Math::Dot(r.direction(), r.direction());
	auto b = 2.0 * Math::Dot(oc, r.direction());
	auto c = Math::Dot(oc, oc) - radius * radius;
	auto d = b * b - 4 * a * c;
	return d > 0;
#endif
}
