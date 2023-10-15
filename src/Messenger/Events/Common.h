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

    enum class MouseButton
    {
        None = 0,
        Left = 1,
        Middle = 2,
        Right = 3
    };

    struct KeyEvent
        : Event
    {
        KeyEventType type = KeyEventType::Undefined;
        int code = -1;

        KeyEvent(KeyEventType eventType, int keyCode);
    };

    struct MouseButtonEvent
        : Event
    {
        KeyEventType type = KeyEventType::Undefined;
        MouseButton button = MouseButton::None;
        int x = 0;
        int y = 0;

        MouseButtonEvent(KeyEventType eventType, MouseButton mouseBtn, int posX, int posY);
    };

    struct MouseMoveEvent
        : Event
    {
        int x = 0;
        int y = 0;
        int dx = 0;
        int dy = 0;

        MouseMoveEvent(int posX, int posY, int diffX, int diffY);
    };

    struct Quit : Event
    {
    };
}