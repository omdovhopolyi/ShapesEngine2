#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Enums/InputEventTypeEnum.h"
#include "Enums/MouseButtonEnum.h"
#include "UI/UIWindowContext.h"

namespace shen
{
    struct InputComponentsDirty : Event
    {
        std::string windowId;

        InputComponentsDirty(const std::string& winId = {}) : windowId(winId) {}
    };

    struct OpenWindowEvent : Event
    {
        UIWindowContext context;

        OpenWindowEvent(UIWindowContext windowContext) : context(windowContext) {}
    };
}
