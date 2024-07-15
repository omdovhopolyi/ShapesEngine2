#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Enums/InputEventTypeEnum.h"
//#include "Enums/KeyModeEnum.h"
#include "Enums/MouseButtonEnum.h"

namespace shen
{
    struct InputComponentsDirty : Event
    {
        std::string windowId;

        InputComponentsDirty(const std::string& winId = {}) : windowId(winId) {}
    };
}
