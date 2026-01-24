#pragma once

#include "DLLImport/Include/Module/Module.h"

#include <Windows.h>

struct ModuleData
{
	HMODULE           hmod;
	PFN_CreateModule  pfn_create;
	PFN_DestroyModule pfn_destroy;
	IModule*          module;
};

class ModuleManager
{
public:

private:
	std::vector<ModuleData> m_modules;
};
