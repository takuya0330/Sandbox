#pragma once

#include <initializer_list> // std::initializer_list
#include <sstream>          // std::wostringstream
#include <type_traits>      // std::forward

class Log
{
public:
	static void Consolef(const char* format, ...);

	static void Consolef(const wchar_t* format, ...);

	template< class... T >
	static void Console(T&&... args)
	{
		std::wostringstream outs;
		static_cast< void >(std::initializer_list< int > { (outs << std::forward< T >(args), 0)... });
		Consolef(L"%s\n", outs.str().c_str());
	}

	static void Outputf(const char* format, ...);

	static void Outputf(const wchar_t* format, ...);

	template< class... T >
	static void Output(T&&... args)
	{
		std::wostringstream outs;
		static_cast< void >(std::initializer_list< int > { (outs << std::forward< T >(args), 0)... });
		Outputf(L"%s\n", outs.str().c_str());
	}

private:
};

// https://learn.microsoft.com/en-us/cpp/build/formatting-the-output-of-a-custom-build-step-or-build-event?view=msvc-170

// \n[level] message\nfile(line), function
#define __VS_OUTPUT_FORMAT(level, ...) Log::Output("\n[ ", level, " ] ", __VA_ARGS__, "\n", __FILE__, "(", __LINE__, "): ", __FUNCSIG__, "\n")

#define __VS_OUTPUT_ERROR(...)   __VS_OUTPUT_FORMAT("ERROR", __VA_ARGS__)
#define __VS_OUTPUT_WARNING(...) __VS_OUTPUT_FORMAT("WARNING", __VA_ARGS__)
