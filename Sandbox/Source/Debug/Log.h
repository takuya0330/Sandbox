#pragma once

#include <initializer_list> // std::initializer_list
#include <sstream>          // std::wostringstream
#include <type_traits>      // std::forward

class Log
{
public:
	static void Consolef(const char* format, ...);

	static void Consolef(const wchar_t* format, ...);

	template<class... T>
	static void Console(T&&... args)
	{
		std::wostringstream outs;
		static_cast<void>(std::initializer_list<int> { (outs << std::forward<T>(args), 0)... });
		Consolef(L"%s\n", outs.str().c_str());
	}

	static void Outputf(const char* format, ...);

	static void Outputf(const wchar_t* format, ...);

	template<class... T>
	static void Output(T&&... args)
	{
		std::wostringstream outs;
		static_cast<void>(std::initializer_list<int> { (outs << std::forward<T>(args), 0)... });
		Outputf(L"%s\n", outs.str().c_str());
	}

private:
};
