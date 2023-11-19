#pragma once

#include "Event.h"
#include "ECS/Entity.h"

namespace shen
{
    enum class InputEventType
    {
        Undefined,
        Up,
        Down,
        Hold,
        MouseMove,
        Scroll
    };

    enum class KeyMode
    {
        None,
        Crtl,
        Alt,
        Shift
    };

    enum class MouseButton
    {
        None,
        Left,
        Middle,
        Right
    };

    struct KeyEvent
        : Event
    {
        InputEventType type = InputEventType::Undefined;
        int code = -1;
        KeyMode mode = KeyMode::None;

        KeyEvent(InputEventType eventType, int keyCode, KeyMode keyMode);
    };

    struct MouseButtonEvent
        : Event
    {
        InputEventType type = InputEventType::Undefined;
        MouseButton button = MouseButton::None;
        KeyMode mode = KeyMode::None;
        int x = 0;
        int y = 0;

        MouseButtonEvent(InputEventType eventType, MouseButton mouseBtn, KeyMode keyMode, int posX, int posY);
    };

    struct MouseMoveEvent
        : Event
    {
        int x = 0;
        int y = 0;
        int dx = 0;
        int dy = 0;
        KeyMode mode = KeyMode::None;

        MouseMoveEvent(int posX, int posY, int diffX, int diffY, KeyMode keyMode);
    };

    struct Quit : Event
    {
    };
}