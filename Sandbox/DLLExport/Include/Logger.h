#pragma once

#include "DLL.h"

namespace Logger {

extern "C" DLL_API void OutputA(const char* format, ...);
extern "C" DLL_API void OutputW(const wchar_t* format, ...);

extern "C" DLL_API void ConsoleA(const char* format, ...);
extern "C" DLL_API void ConsoleW(const wchar_t* format, ...);

using FnOutputA  = void (*)(const char* format, ...);
using FnOutputW  = void (*)(const wchar_t* format, ...);
using FnConsoleA = void (*)(const char* format, ...);
using FnConsoleW = void (*)(const wchar_t* format, ...);

} // namespace Logger
