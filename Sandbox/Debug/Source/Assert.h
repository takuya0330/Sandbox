#pragma once

#include <assert.h>
#include <intrin.h>

#include "Log.h"

#undef _ASSERT
#undef _ASSERT_MSG
#undef _ASSERT_RETURN

#define __MACRO_BEG \
	do              \
	{
#define __MACRO_END \
	}               \
	while (0)

#define _ASSERT(expression)                               \
	__MACRO_BEG                                           \
	__VS_OUTPUT_ERROR("Assertion failed: ", #expression); \
	assert(expression);                                   \
	__MACRO_END

#define _ASSERT_MSG(expression, ...)                                         \
	__MACRO_BEG                                                              \
	__VS_OUTPUT_ERROR("Assertion failed: ", #expression, ", ", __VA_ARGS__); \
	assert(expression);                                                      \
	__MACRO_END

#define _ASSERT_RETURN(expression, ...)                         \
	__MACRO_BEG                                                 \
	if (!(expression))                                          \
	{                                                           \
		__VS_OUTPUT_WARNING("Assertion failed: ", #expression); \
		__debugbreak();                                         \
		return __VA_ARGS__;                                     \
	}                                                           \
	__MACRO_END
