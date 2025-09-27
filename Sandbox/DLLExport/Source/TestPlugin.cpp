#include "../DLLImport/Include/Plugin.h"

#include "Include/Logger.h"

class DLL_API TestPlugin : public IPlugin
{
public:
	void Activate() override
	{
		Logger::ConsoleA("TestPlugin activated!");
	}
	void Deactivate() override
	{
		Logger::ConsoleA("TestPlugin deactivated!");
	}
};

extern "C" DLL_API IPlugin* CreatePlugin()
{
    return new TestPlugin();
}

extern "C" DLL_API void DestroyPlugin(IPlugin* plugin)
{
    delete plugin;
}
