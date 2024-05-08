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
    };
}
