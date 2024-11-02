#pragma once

#include "Plugin.h"

class TestPlugin : public IPlugin
{
public:
    TestPlugin() = default;

    ~TestPlugin() override = default;

    void Activate() override;

    void Deactivate() override;

    void GetRequiredPlugins(std::vector<std::string>& required_plugins) override;

    void GetOptionalPlugins(std::vector<std::string>& optional_plugins) override;

    const char* GetNameA() const override { return "TestPlugin"; }

    const wchar_t* GetNameW() const override { return L"TestPlugin"; }
};

DECLARE_PLUGIN_CLASS(DLL_API, TestPlugin, TestPlugin);
