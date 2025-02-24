#pragma once

#define RAYTRACING_USING_MATH_DXM  (1)
#define RAYTRACING_USING_MATH_MATH (0)

#define RAYTRACING_01_OUTPUT_PPM (1)
#define RAYTRACING_02_VECTOR     (1)
#define RAYTRACING_03_RAY        (1)
#define RAYTRACING_04_HIT_SPHERE (0)

#if RAYTRACING_USING_MATH_DXM
#include "../../DirectXMathHelper/Source/DirectXMathHelper.h"

using namespace XMH;

using int2 = DirectX::XMINT2;
using int3 = DirectX::XMINT3;
using int4 = DirectX::XMINT4;

using float2 = DirectX::XMFLOAT2;
using float3 = DirectX::XMFLOAT3;
using float4 = DirectX::XMFLOAT4;

#elif RAYTRACING_USING_MATH_MATH
#include "../../Math/Source/Math.h"
#else
#error Math library not found.
#endif
