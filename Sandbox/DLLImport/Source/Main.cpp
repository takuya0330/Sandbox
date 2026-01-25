#include "DLLImport/Include/Module/Module.h"

#include <Windows.h>
#include <iostream>

// #pragma comment(lib, "DLLExport1.lib")

int main(int, char**)
{
	HMODULE export1_hmod = LoadLibraryA("DLLExport1.dll");
	if (!export1_hmod)
	{
		std::cerr << "DLL load failed.\n";
		return 1;
	}

	auto export1_create_module = (PFN_CreateModule)GetProcAddress(export1_hmod, "CreateModule");
	if (!export1_create_module)
	{
		std::cerr << "GetProcAddress failed.\n";
		return 1;
	}

	auto export1_destroy_module = (PFN_DestroyModule)GetProcAddress(export1_hmod, "DestroyModule");
	if (!export1_destroy_module)
	{
		std::cerr << "GetProcAddress failed.\n";
		return 1;
	}

	auto export1 = export1_create_module();
	if (!export1)
	{
		std::cerr << "CreateModule failed.\n";
		return 1;
	}

	export1->Activate();
	export1->Deactivate();

	export1_destroy_module(export1);
	export1 = nullptr;

	FreeLibrary(export1_hmod);

	return 0;
}
