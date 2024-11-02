#pragma once

#include <vector>
#include <string>

#include "Common.h"

class IPlugin
{
public:
    virtual ~IPlugin() = default;

    virtual void Activate() = 0;

    virtual void Deactivate() = 0;

    virtual void GetRequiredPlugins(std::vector<std::string>& required_plugins) = 0;

    virtual void GetOptionalPlugins(std::vector<std::string>& optional_plugins) = 0;

    virtual const char* GetNameA() const = 0;

    virtual const wchar_t* GetNameW() const = 0;
};

using CreatePluginClassFunction = IPlugin * (*)();
constexpr const char* CreatePluginClassFunctionNameA = "CreatePluginClass";
constexpr const wchar_t* CreatePluginClassFunctionNameW = L"CreatePluginClass";

#if defined(UNICODE)
#define CreatePluginClassFunctionName CreatePluginClassFunctionNameA
#else
#define CreatePluginClassFunctionName CreatePluginClassFunctionNameW
#endif

using DestroyPluginClassFunction = void(*)(IPlugin*);
constexpr const char* DestroyPluginClassFunctionNameA = "DestroyPluginClass";
constexpr const wchar_t* DestroyPluginClassFunctionNameW = L"DestroyPluginClass";

#if defined(UNICODE)
#define DestroyPluginClassFunctionName DestroyPluginClassFunctionNameA
#else
#define DestroyPluginClassFunctionName DestroyPluginClassFunctionNameW
#endif

#define DECLARE_PLUGIN_CLASS(API_NAME, MODULE_NAME, MODULE_CLASSNAME)               \
extern "C" API_NAME IPlugin* CreatePluginClass() { return new MODULE_CLASSNAME; }   \
extern "C" API_NAME void DestroyPluginClass(IPlugin* plugin) { delete plugin; }
