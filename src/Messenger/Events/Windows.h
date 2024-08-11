#pragma once

#include "Event.h"
#include "UI/UIWindowContext.h"

namespace shen
{
    struct OpenWindowEvent
        : Event
    {
        UIWindowContext context;

        OpenWindowEvent(UIWindowContext context);
    };
}