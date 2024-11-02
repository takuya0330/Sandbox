#include "../DLLExport/Plugin.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>

int main(int, char**)
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto hmod = LoadLibrary(L"../../x64/Debug/DLLExport.dll");
    if (hmod == NULL)
    {
        std::cout << "ERROR: LoadLibrary failed." << std::endl;
        return -1;
    }

    auto create_function = (CreatePluginClassFunction)GetProcAddress(hmod, CreatePluginClassFunctionName);
    if (create_function == NULL)
    {
        std::cout << "ERROR: GetProcAddress(CreatePluginClass) failed." << std::endl;
        return -1;
    }

    auto destroy_function = (DestroyPluginClassFunction)GetProcAddress(hmod, DestroyPluginClassFunctionName);
    if (destroy_function == NULL)
    {
        std::cout << "ERROR: GetProcAddress(DestroyPluginClass) failed." << std::endl;
        return -1;
    }

    auto plugin = create_function();

    std::vector<std::string> required_plugins, optional_plugins;
    plugin->GetRequiredPlugins(required_plugins);
    plugin->GetOptionalPlugins(optional_plugins);
    plugin->Activate();
    plugin->Deactivate();

    destroy_function(plugin);
    plugin = nullptr;

    FreeLibrary(hmod);

    return 0;
}
