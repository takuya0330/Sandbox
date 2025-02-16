#pragma once

#include <intrin.h>

#include "Log.h"

#undef _ASSERT
#undef _ASSERT_MSG
#undef _ASSERT_RETURN

#if defined(_DEBUG)
#define _DEBUG_BREAK __debugbreak()
#else
#define _DEBUG_BREAK
#endif

// https://learn.microsoft.com/en-us/cpp/build/formatting-the-output-of-a-custom-build-step-or-build-event?view=msvc-170

#define _VS_OUTPUT_FORMAT(level, ...) Log::Output(__FILE__, "(", __LINE__, "): ", #level, ": ", __FUNCSIG__, ": ", __VA_ARGS__)

#define _VS_OUTPUT_ERROR(...)   _VS_OUTPUT_FORMAT(ERROR, __VA_ARGS__)
#define _VS_OUTPUT_WARNING(...) _VS_OUTPUT_FORMAT(WARNING, __VA_ARGS__)

#define _MACRO_BEG \
	do             \
	{
#define _MACRO_END \
	}              \
	while (0)

#define _DEBUG_BREAK_IF_FALSE(expr, function) \
	if (!(expr))                              \
	{                                         \
		function;                             \
		_DEBUG_BREAK;                         \
	}

#define _ASSERT(expr)                                                          \
	_MACRO_BEG                                                                 \
	_DEBUG_BREAK_IF_FALSE(expr, _VS_OUTPUT_ERROR("Assertion failed: ", #expr)) \
	_MACRO_END

#define _ASSERT_MSG(expr, ...)                                                              \
	_MACRO_BEG                                                                              \
	_DEBUG_BREAK_IF_FALSE(expr, _VS_OUTPUT_ERROR("Assertion failed: ", #expr, __VA_ARGS__)) \
	_MACRO_END

#define _ASSERT_RETURN(expr, ...)                      \
	_MACRO_BEG                                         \
	if (!(expr))                                       \
	{                                                  \
		_VS_OUTPUT_ERROR("Assertion failed: ", #expr); \
		_DEBUG_BREAK;                                  \
		return __VA_ARGS__;                            \
	}                                                  \
	_MACRO_END
