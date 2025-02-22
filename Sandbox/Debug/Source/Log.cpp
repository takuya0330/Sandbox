#include "Log.h"

#include <Windows.h> // OutputDebugStringA, OutputDebugStringW
#include <stdarg.h>  // va_start, va_end

namespace {

static constexpr size_t kMaxBufferNum = 4096;

} // namespace

void Log::Consolef(const char* format, ...)
{
#if defined(_CONSOLE)
	char    buffer[kMaxBufferNum] = {};
	va_list ap;
	va_start(ap, format);
	vsprintf_s(buffer, kMaxBufferNum, format, ap);
	va_end(ap);
	printf("%s\n", buffer);
#endif
}

void Log::Consolef(const wchar_t* format, ...)
{
#if defined(_CONSOLE)
	wchar_t buffer[kMaxBufferNum] = {};
	va_list ap;
	va_start(ap, format);
	vswprintf(buffer, kMaxBufferNum, format, ap);
	va_end(ap);
	wprintf(L"%s\n", buffer);
#endif
}

void Log::Outputf(const char* format, ...)
{
	char    buffer[kMaxBufferNum] = {};
	va_list ap;
	va_start(ap, format);
	vsprintf_s(buffer, kMaxBufferNum, format, ap);
	va_end(ap);
	OutputDebugStringA(buffer);
}

void Log::Outputf(const wchar_t* format, ...)
{
	wchar_t buffer[kMaxBufferNum] = {};
	va_list ap;
	va_start(ap, format);
	vswprintf(buffer, kMaxBufferNum, format, ap);
	va_end(ap);
	OutputDebugStringW(buffer);
}
