#pragma once

#include "Utils/Storage.h"

namespace shen
{
    class SystemsManager;

    struct ContextBase
    {
        SystemsManager* systems = nullptr;
        Storage vars;
    };
}