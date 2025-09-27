#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#if defined(_USRDLL)
#if defined(DLLEXPORT_EXPORTS)
#define DLL_API DLL_EXPORT
#else
#define DLL_API DLL_IMPORT
#endif
#else
#define DLL_API
#endif
