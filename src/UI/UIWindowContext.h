#pragma once

#include <string>
#include <any>
#include <map>

namespace shen
{
    class SystemsManager;

    struct UIWindowContext
    {
        std::string windowId;
        SystemsManager* systems = nullptr;
        std::map<std::string, std::any> vars;
    };
}