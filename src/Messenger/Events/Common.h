#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Enums/InputEventTypeEnum.h"
#include "Enums/MouseButtonEnum.h"

namespace shen
{
    struct KeyEvent
        : Event
    {
        InputEventType type = InputEventType::Undefined;
        int code = -1;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        KeyEvent(InputEventType eventType, int keyCode, bool altMode, bool shiftMode, bool ctrlMode);
    };

    struct MouseButtonEvent
        : Event
    {
        InputEventType type = InputEventType::Undefined;
        MouseButton button = MouseButton::None;
        int x = 0;
        int y = 0;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        MouseButtonEvent(InputEventType eventType, MouseButton mouseBtn, int posX, int posY, bool altMode, bool shiftMode, bool ctrlMode);
    };

    struct MouseMoveEvent
        : Event
    {
        MouseButton button = MouseButton::None;
        int x = 0;
        int y = 0;
        int dx = 0;
        int dy = 0;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        MouseMoveEvent(MouseButton mouseBtn, int posX, int posY, int diffX, int diffY, bool altMode, bool shiftMode, bool ctrlMode);
    };

    struct MouseWheelEvent
        : Event
    {
        int x = 0;
        int y = 0;
        float scroll = 0;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        MouseWheelEvent(int posX, int posY, float scrl, bool altMode, bool shiftMode, bool ctrlMode);
    };

    struct Quit : Event {};

    struct MapLoadedEvent : Event
    {
        std::string mapId;

        MapLoadedEvent(const std::string& id);
    };

    struct LostFocus : Event {};

    struct GainedFocus : Event {};

    struct PauseGameEvent : Event {};
}
