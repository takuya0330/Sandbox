#include "TestPlugin.h"

#include <iostream>

void TestPlugin::Activate()
{
    std::cout << "TestPlugin: Activate" << std::endl;
}

void TestPlugin::Deactivate()
{
    std::cout << "TestPlugin: Deactivate" << std::endl;
}

void TestPlugin::GetRequiredPlugins(std::vector<std::string>& required_plugins)
{
    
}

void TestPlugin::GetOptionalPlugins(std::vector<std::string>& optional_plugins)
{

}
