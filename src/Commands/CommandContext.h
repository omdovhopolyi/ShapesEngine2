#pragma once

#include "ECS/Entity.h"
#include "ECS/SystemsManager.h"
#include "Utils/Storage.h"

namespace shen
{
    struct CommandContext
    {
        Entity entity;
        SystemsManager* systems = nullptr;
        Storage vars;
    };
}
