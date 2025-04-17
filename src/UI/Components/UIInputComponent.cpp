#pragma once

#include "UIInputComponent.h"
#include "Serialization/Types/SerializableFieldInt.h"

namespace shen
{
    void UIInputComponent::RegisterProperties()
    {
        UIComponent::RegisterProperties();
        RegisterVar<SerializableFieldInt>(_inputPriority, "priority");
    }

    void UIInputComponent::SetInputPriority(int priority)
    {
        _inputPriority = priority;
    }

    int UIInputComponent::GetInputPriority() const
    {
        return _inputPriority;
    }
}
