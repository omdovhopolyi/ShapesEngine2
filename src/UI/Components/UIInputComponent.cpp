#pragma once

#include "UIInputComponent.h"
#include "UI/UIWindow.h"
#include "Serialization/Types/SerializableFieldInt.h"

namespace shen
{
    void UIInputComponent::RegisterProperties()
    {
        UIComponent::RegisterProperties();
        RegisterVar<SerializableFieldInt>(_inputPriority, "priority");
    }

    void UIInputComponent::AfterLoad()
    {
        UIComponent::AfterLoad();

        if (!_id.empty())
        {
            auto window = GetWindow();
            window->MapInputComponent(_id, std::static_pointer_cast<UIInputComponent>(shared_from_this()));
        }
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
