#pragma once

#include <DirectXMath.h>

namespace XMH {

#define _ARITHMETIC_V2(OP) v1.x OP v2.x, v1.y OP v2.y
#define _ARITHMETIC_V3(OP) v1.x OP v2.x, v1.y OP v2.y, v1.z OP v2.z
#define _ARITHMETIC_V4(OP) v1.x OP v2.x, v1.y OP v2.y, v1.z OP v2.z, v1.w OP v2.w

#define _ARITHMETIC_T2(OP) v1.x OP v2, v1.y OP v2
#define _ARITHMETIC_T3(OP) v1.x OP v2, v1.y OP v2, v1.z OP v2
#define _ARITHMETIC_T4(OP) v1.x OP v2, v1.y OP v2, v1.z OP v2, v1.w OP v2

#define _ARITHMETIC_V(N, OP, ...) _ARITHMETIC_V##N(OP)
#define _ARITHMETIC_T(N, OP, ...) _ARITHMETIC_T##N(OP)

#define _ARITHMETIC_OPERATOR(TYPE1, TYPE2, N, OP)                                           \
	inline static constexpr TYPE1 operator OP(const TYPE1& v1, const TYPE2& v2)             \
	{                                                                                       \
		return TYPE1(_ARITHMETIC_V(N, OP));                                                 \
	}                                                                                       \
	inline static constexpr TYPE1 operator OP(const TYPE1& v1, const decltype(TYPE2::x) v2) \
	{                                                                                       \
		return TYPE1(_ARITHMETIC_T(N, OP));                                                 \
	}

#define _ASSIGNMENT_V2(OP) \
	v1.x OP v2.x;          \
	v1.y OP v2.y
#define _ASSIGNMENT_V3(OP) \
	v1.x OP v2.x;          \
	v1.y OP v2.y;          \
	v1.z OP v2.z
#define _ASSIGNMENT_V4(OP) \
	v1.x OP v2.x;          \
	v1.y OP v2.y;          \
	v1.z OP v2.z;          \
	v1.w OP v2.w

#define _ASSIGNMENT_T2(OP) \
	v1.x OP v2;            \
	v1.y OP v2
#define _ASSIGNMENT_T3(OP) \
	v1.x OP v2;            \
	v1.y OP v2;            \
	v1.z OP v2
#define _ASSIGNMENT_T4(OP) \
	v1.x OP v2;            \
	v1.y OP v2;            \
	v1.z OP v2;            \
	v1.w OP v2

#define _ASSIGNMENT_V(N, OP) _ASSIGNMENT_V##N(OP)
#define _ASSIGNMENT_T(N, OP) _ASSIGNMENT_T##N(OP)

#define _ASSIGNMENT_OPERATOR(TYPE1, TYPE2, N, OP)                          \
	inline static void operator OP(TYPE1& v1, const TYPE2& v2)             \
	{                                                                      \
		_ASSIGNMENT_V(N, OP);                                              \
	}                                                                      \
	inline static void operator OP(TYPE1& v1, const decltype(TYPE2::x) v2) \
	{                                                                      \
		_ASSIGNMENT_T(N, OP);                                              \
	}

#define _XMH_ARITHMETIC_OPERATORS(TYPE1, TYPE2, N)  \
	_ARITHMETIC_OPERATOR(TYPE1##N, TYPE2##N, N, +); \
	_ARITHMETIC_OPERATOR(TYPE1##N, TYPE2##N, N, -); \
	_ARITHMETIC_OPERATOR(TYPE1##N, TYPE2##N, N, *); \
	_ARITHMETIC_OPERATOR(TYPE1##N, TYPE2##N, N, /)

#define _XMH_ASSIGNMENT_OPERATORS(TYPE1, TYPE2, N)   \
	_ASSIGNMENT_OPERATOR(TYPE1##N, TYPE2##N, N, +=); \
	_ASSIGNMENT_OPERATOR(TYPE1##N, TYPE2##N, N, -=); \
	_ASSIGNMENT_OPERATOR(TYPE1##N, TYPE2##N, N, *=); \
	_ASSIGNMENT_OPERATOR(TYPE1##N, TYPE2##N, N, /=)

#define _XMH_OPERATORS(TYPE1, TYPE2)            \
	_XMH_ARITHMETIC_OPERATORS(TYPE1, TYPE2, 2); \
	_XMH_ARITHMETIC_OPERATORS(TYPE1, TYPE2, 3); \
	_XMH_ARITHMETIC_OPERATORS(TYPE1, TYPE2, 4); \
	_XMH_ASSIGNMENT_OPERATORS(TYPE1, TYPE2, 2); \
	_XMH_ASSIGNMENT_OPERATORS(TYPE1, TYPE2, 3); \
	_XMH_ASSIGNMENT_OPERATORS(TYPE1, TYPE2, 4)

_XMH_OPERATORS(DirectX::XMFLOAT, DirectX::XMFLOAT);
_XMH_OPERATORS(DirectX::XMINT, DirectX::XMINT);
_XMH_OPERATORS(DirectX::XMUINT, DirectX::XMUINT);

inline DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& f, const DirectX::XMMATRIX& m)
{
	auto v = DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&f), m);

    DirectX::XMFLOAT3 out(0, 0, 0);
	DirectX::XMStoreFloat3(&out, v);

	return out;
}

inline DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4& f, const DirectX::XMMATRIX& m)
{
	auto v = DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&f), m);

	DirectX::XMFLOAT4 out(0, 0, 0, 0);
	DirectX::XMStoreFloat4(&out, v);

	return out;
}

} // namespace XMH
