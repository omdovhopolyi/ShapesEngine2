#pragma once

#include "Event.h"
#include "ECS/Entity.h"

namespace shen
{
    enum class KeyEventType
    {
        Undefined,
        Up,
        Down,
        Hold
    };

    struct KeyEvent
        : Event
    {
        KeyEventType type = KeyEventType::Undefined;
        int code = -1;

        KeyEvent(KeyEventType eventType, int keyCode);
    };

    struct Quit : Event
    {
    };
}