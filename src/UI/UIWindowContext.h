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
        std::map<std::string, std::any> vars;
    };
}
