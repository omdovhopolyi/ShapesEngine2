#pragma once

#include "Enums/MouseButtonEnum.h"
#include "Enums/InputEventTypeEnum.h"

namespace shen
{
    struct InputType
    {
        int keyCode = -1;
        MouseButton mouseButton = MouseButton::None;
        InputEventType type = InputEventType::Undefined;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        friend bool operator < (const InputType& left, const InputType& right);
        friend bool operator == (const InputType& left, const InputType& right);
    };
}
