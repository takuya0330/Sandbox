#include "DLLImport/Include/Module/Module.h"

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
