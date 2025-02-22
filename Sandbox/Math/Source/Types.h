#pragma once

#include <cstdint>

namespace Math {

template< class T > struct Vector2;
template< class T > struct Vector3;
template< class T > struct Vector4;
template< class T > struct Matrix2;
template< class T > struct Matrix3;
template< class T > struct Matrix4;
template< class T = double > struct Quatarnion;

} // namespace Math

using int2 = Math::Vector2< int32_t >;
using int3 = Math::Vector3< int32_t >;
using int4 = Math::Vector4< int32_t >;

using uint2 = Math::Vector2< uint32_t >;
using uint3 = Math::Vector3< uint32_t >;
using uint4 = Math::Vector4< uint32_t >;

using float2 = Math::Vector2< float >;
using float3 = Math::Vector3< float >;
using float4 = Math::Vector4< float >;

using float2x2 = Math::Matrix2< float >;
using float3x3 = Math::Matrix3< float >;
using float4x4 = Math::Matrix4< float >;
