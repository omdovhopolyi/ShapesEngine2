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

        OpenWindowEvent(const std::string& windowId) : context({ windowId }) {}
        OpenWindowEvent(UIWindowContext windowContext) : context(windowContext) {}
    };

    struct CloseWindowEvent : Event
    {
        std::string windowId;

        CloseWindowEvent(const std::string& id) : windowId(id) {}
    };

    struct CloseTopWindowEvent : Event {};
}
