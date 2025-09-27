#include "../Include/Logger.h"

#include <cstdarg>
#include <cstdio>

namespace Logger {
namespace {
constexpr size_t kMaxBufferSize = 1024;
}

extern "C" void OutputA(const char* format, ...)
{
	char    buffer[kMaxBufferSize] = {};
	va_list ap;
	va_start(ap, format);
	vsprintf_s(buffer, kMaxBufferSize, format, ap);
	va_end(ap);
	OutputDebugStringA(buffer);
}

extern "C" void OutputW(const wchar_t* format, ...)
{
	wchar_t buffer[kMaxBufferSize] = {};
	va_list ap;
	va_start(ap, format);
	vswprintf(buffer, kMaxBufferSize, format, ap);
	va_end(ap);
	OutputDebugStringW(buffer);
}

extern "C" void ConsoleA(const char* format, ...)
{
	char    buffer[kMaxBufferSize] = {};
	va_list ap;
	va_start(ap, format);
	vsprintf_s(buffer, kMaxBufferSize, format, ap);
	va_end(ap);
	printf("%s\n", buffer);
}

extern "C" void ConsoleW(const wchar_t* format, ...)
{
	wchar_t buffer[kMaxBufferSize] = {};
	va_list ap;
	va_start(ap, format);
	vswprintf(buffer, kMaxBufferSize, format, ap);
	va_end(ap);
	wprintf(L"%s\n", buffer);
}

} // namespace Logger
