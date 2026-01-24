#include "DLLImport/Include/Module/Module.h"

#include "DLLExport1/Include/Test1.h"
#include "DLLExport1/Include/Test2.h"

#include <Windows.h>

class Export1 : public IModule
{
public:
	Export1() = default;

	void Activate() override
	{
	}

	void Deactivate() override
	{
	}

    void RegisterTypeInfos(std::vector<const STL::TypeInfo*>& type_infos) override
    {
		type_infos.emplace_back(Test1::GetTypeInfo());
		type_infos.emplace_back(Test2::GetTypeInfo());
    }

	void GetDependentModules(std::vector<std::string>& dependent) override
	{
		dependent.emplace_back("Dep1");
		dependent.emplace_back("Dep2");
		dependent.emplace_back("Dep3");
	}

	void GetOptionalModules(std::vector<std::string>& optional) override
	{
		optional.emplace_back("Opt1");
	}

    ModuleType GetType() const override
    {
		return ModuleType::kRuntime;
    }
};
DECLARE_MODULE(DLL_API, Export1);

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD                     ul_reason_for_call,
    LPVOID                    lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
