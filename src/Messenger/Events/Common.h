#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Enums/InputEventTypeEnum.h"
#include "Enums/KeyModeEnum.h"
#include "Enums/MouseButtonEnum.h"

namespace shen
{
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

    struct MouseWheelEvent
        : Event
    {
        int x = 0;
        int y = 0;
        int scroll = 0;
        KeyMode mode = KeyMode::None;

        MouseWheelEvent(int posX, int posY, int scrl, KeyMode keyMode);
    };

    struct Quit : Event
    {
    };
}