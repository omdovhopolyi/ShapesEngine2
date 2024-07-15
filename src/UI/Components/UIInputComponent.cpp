#pragma once

#include "UIInputComponent.h"

namespace shen
{
    void UIInputComponent::SetInputPriority(int priority)
    {
        _inputPriority = priority;
    }

    int UIInputComponent::GetInputPriority() const
    {
        return _inputPriority;
    }
}
