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

#define VS_OUTPUT_ERROR(...)   Log::Output(__FILE__, "(", __LINE__, "): ERROR: ", __FUNCSIG__, ": ", __VA_ARGS__)
#define VS_OUTPUT_WARNING(...) Log::Output(__FILE__, "(", __LINE__, "): WARNING: ", __FUNCSIG__, ": ", __VA_ARGS__)

#define _ASSERT(expr)                                     \
	do                                                    \
	{                                                     \
		if (!(expr))                                      \
		{                                                 \
			VS_OUTPUT_ERROR("Assertion failed: ", #expr); \
			_DEBUG_BREAK;                                 \
		}                                                 \
	} while (0)

#define _ASSERT_MSG(expr, ...)                                         \
	do                                                                 \
	{                                                                  \
		if (!(expr))                                                   \
		{                                                              \
			VS_OUTPUT_ERROR("Assertion failed: ", #expr, __VA_ARGS__); \
			_DEBUG_BREAK;                                              \
		}                                                              \
	} while (0)

#define _ASSERT_RETURN(expr, ...) \
	do                            \
	{                             \
		if (!(expr))              \
		{                         \
			_ASSERT(expr);        \
			return __VA_ARGS__;   \
		}                         \
	} while (0)
