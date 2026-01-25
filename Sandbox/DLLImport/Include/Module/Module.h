#pragma once

#include "DLLImport/Include/DLL.h"

class DLL_API IModule
{
public:
	~IModule() = default;

	virtual void Activate() = 0;

	virtual void Deactivate() = 0;
};

using PFN_CreateModule  = IModule* (*)();
using PFN_DestroyModule = void (*)(IModule*);

#if defined(_USRDLL)
#define DECLARE_MODULE(API, ModuleClass)          \
	extern "C" API IModule* CreateModule()        \
	{                                             \
		return new ModuleClass();                 \
	}                                             \
	extern "C" API void DestroyModule(IModule* p) \
	{                                             \
		delete p;                                 \
	}
#else
#define DECLARE_MODULE(API, ModuleClass)
#endif
