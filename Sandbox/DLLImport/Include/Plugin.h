#pragma once

#include "Include/DLL.h"

class DLL_API IPlugin
{
public:
	virtual ~IPlugin() = default;

	virtual void Activate() = 0;

	virtual void Deactivate() = 0;
};

using FnCreatePlugin  = IPlugin* (*)();
using FnDestroyPlugin = void (*)(IPlugin*);

extern "C" DLL_API IPlugin* CreatePlugin();
extern "C" DLL_API void     DestroyPlugin(IPlugin* plugin);
