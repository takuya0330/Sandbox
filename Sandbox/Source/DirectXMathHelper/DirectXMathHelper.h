#pragma once

#include <DirectXMath.h>

namespace XMH {

using namespace DirectX;

#define _ARITHMETIC_V2(OP) v1.x OP v2.x, v1.y OP v2.y
#define _ARITHMETIC_V3(OP) v1.x OP v2.x, v1.y OP v2.y, v1.z OP v2.z
#define _ARITHMETIC_V4(OP) v1.x OP v2.x, v1.y OP v2.y, v1.z OP v2.z, v1.w OP v2.w

#define _ARITHMETIC_T2(OP) v1.x OP v2, v1.y OP v2
#define _ARITHMETIC_T3(OP) v1.x OP v2, v1.y OP v2, v1.z OP v2
#define _ARITHMETIC_T4(OP) v1.x OP v2, v1.y OP v2, v1.z OP v2, v1.w OP v2

#define _ARITHMETIC_V(N, OP, ...) _ARITHMETIC_V##N(OP)
#define _ARITHMETIC_T(N, OP, ...) _ARITHMETIC_T##N(OP)

#define _ARITHMETIC_OPERATOR(TYPE, N, OP)                                                                                       \
    inline static constexpr TYPE operator OP(const TYPE& v1, const TYPE& v2) { return TYPE(_ARITHMETIC_V(N, OP)); }             \
    inline static constexpr TYPE operator OP(const TYPE& v1, const decltype(TYPE::x) v2) { return TYPE(_ARITHMETIC_T(N, OP)); }

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

#define _ASSIGNMENT_OPERATOR(TYPE, N, OP)                                                           \
    inline static void operator OP(TYPE& v1, const TYPE& v2) { _ASSIGNMENT_V(N, OP); }              \
    inline static void operator OP(TYPE& v1, const decltype(TYPE::x) v2) { _ASSIGNMENT_T(N, OP); }

#define _XMH_ARITHMETIC_OPERATORS(TYPE, N) \
    _ARITHMETIC_OPERATOR(TYPE##N, N, +);   \
    _ARITHMETIC_OPERATOR(TYPE##N, N, -);   \
    _ARITHMETIC_OPERATOR(TYPE##N, N, *);   \
    _ARITHMETIC_OPERATOR(TYPE##N, N, / )

#define _XMH_ASSIGNMENT_OPERATORS(TYPE, N) \
    _ASSIGNMENT_OPERATOR(TYPE##N, N, +=);  \
    _ASSIGNMENT_OPERATOR(TYPE##N, N, -=);  \
    _ASSIGNMENT_OPERATOR(TYPE##N, N, *=);  \
    _ASSIGNMENT_OPERATOR(TYPE##N, N, /= )

_XMH_ARITHMETIC_OPERATORS(XMFLOAT, 2);
_XMH_ARITHMETIC_OPERATORS(XMFLOAT, 3);
_XMH_ARITHMETIC_OPERATORS(XMFLOAT, 4);

_XMH_ASSIGNMENT_OPERATORS(XMFLOAT, 2);
_XMH_ASSIGNMENT_OPERATORS(XMFLOAT, 3);
_XMH_ASSIGNMENT_OPERATORS(XMFLOAT, 4);

_XMH_ARITHMETIC_OPERATORS(XMINT, 2);
_XMH_ARITHMETIC_OPERATORS(XMINT, 3);
_XMH_ARITHMETIC_OPERATORS(XMINT, 4);

_XMH_ASSIGNMENT_OPERATORS(XMINT, 2);
_XMH_ASSIGNMENT_OPERATORS(XMINT, 3);
_XMH_ASSIGNMENT_OPERATORS(XMINT, 4);

_XMH_ARITHMETIC_OPERATORS(XMUINT, 2);
_XMH_ARITHMETIC_OPERATORS(XMUINT, 3);
_XMH_ARITHMETIC_OPERATORS(XMUINT, 4);

_XMH_ASSIGNMENT_OPERATORS(XMUINT, 2);
_XMH_ASSIGNMENT_OPERATORS(XMUINT, 3);
_XMH_ASSIGNMENT_OPERATORS(XMUINT, 4);

}
