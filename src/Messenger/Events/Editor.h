#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Utils/Types.h"

namespace shen
{
    struct OpenEditor : Event { };

    struct CloseEditor : Event { };
}