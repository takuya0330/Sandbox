#pragma once

#define _CRT_SECURE_NO_WARNINGS

// C, C++
#include <iostream>
#include <random>
#include <fstream>

// External Libraries
#define STB_IMAGE_IMPLEMENTATION
#include "../../_External/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../_External/stb/stb_image_write.h"

// Project
#include "Camera.h"
#include "Material.h"

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const RayTracing::Math::Vec3<T>& v)
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}
