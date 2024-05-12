#pragma once

#include "ECS/Entity.h"
#include "ECS/SystemsManager.h"
#include <string>
#include <any>
#include <map>

namespace shen
{
    struct CommandContext
    {
        Entity entity;
        SystemsManager* systems = nullptr;
        std::map<std::string, std::any> vars;

        template<class T>
        const T* GetVar(const std::string& key) const
        {
            if (auto it = vars.find(key); it != vars.end())
            {
                return std::any_cast<const T>(&it->second);
            }

            return nullptr;
        }
    };
}
