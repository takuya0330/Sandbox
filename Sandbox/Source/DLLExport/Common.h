#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined(_USRDLL)
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
