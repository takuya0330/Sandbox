#pragma once

#include "DLLImport/Include/DLL.h"
#include "DLLImport/Include/STL/TypeInfo.h"

#include <string>
#include <vector>

class TypeRegistry;

enum class ModuleType
{
	kRuntime,
	kDevelop,
};

class DLL_API IModule
{
public:
	~IModule() = default;

	virtual void Activate() = 0;

	virtual void Deactivate() = 0;

    virtual void RegisterTypeInfos(std::vector<const STL::TypeInfo*>& type_infos) = 0;

	virtual void GetDependentModules(std::vector<std::string>& dependent) = 0;

	virtual void GetOptionalModules(std::vector<std::string>& optional) = 0;

	virtual ModuleType GetType() const = 0;
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
