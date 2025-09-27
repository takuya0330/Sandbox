#include "Include/Logger.h"
#include "Include/Plugin.h"

#include <Windows.h>
#include <iostream>

#if defined(_UNICODE)
#define Consolef(...) ConsoleW(L##__VA_ARGS__)
#else
#define Consolef(...) ConsoleA(__VA_ARGS__)
#endif

int main(int, char**)
{
	HMODULE hmod = LoadLibraryA("DLLExport.dll");
	if (!hmod)
	{
		std::cerr << "DLL load failed\n";
		return 1;
	}

    auto ConsoleA = (Logger::FnConsoleA)GetProcAddress(hmod, "ConsoleA");
	if (!ConsoleA)
	{
		std::cerr << "GetProcAddress failed\n";
		return 1;
	}

    auto ConsoleW = (Logger::FnConsoleW)GetProcAddress(hmod, "ConsoleW");
	if (!ConsoleW)
	{
		std::cerr << "GetProcAddress failed\n";
		return 1;
	}

    ConsoleA("Hello from DLLImport! [char]");
	ConsoleW(L"Hello from DLLImport! [wchar_t]");

    Consolef("Hello from DLLImport! [macro]");

    auto CreatePlugin = (FnCreatePlugin)GetProcAddress(hmod, "CreatePlugin");
    if (!CreatePlugin)
    {
		std::cerr << "GetProcAddress failed\n";
		return 1;
    }

    auto DestroyPlugin = (FnDestroyPlugin)GetProcAddress(hmod, "DestroyPlugin");
    if (!DestroyPlugin)
	{
		std::cerr << "GetProcAddress failed\n";
		return 1;
	}

    IPlugin* plugin = CreatePlugin();
    if (!plugin)
	{
		std::cerr << "CreatePlugin failed\n";
		return 1;
	}

    plugin->Activate();
	plugin->Deactivate();

    DestroyPlugin(plugin);
	plugin = nullptr;

    FreeLibrary(hmod);

	return 0;
}
