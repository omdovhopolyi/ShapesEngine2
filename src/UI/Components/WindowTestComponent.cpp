#include "WindowTestComponent.h"
#include "UI/Components/UIButtonComponent.h"

namespace shen
{
    WindowTestComponent::WindowTestComponent()
    {
        RegisterReference("testButton", &_button);
    }

    void WindowTestComponent::Init()
    {
        if (auto button = std::dynamic_pointer_cast<UIButtonComponent>(_button.lock()))
        {
            const auto id = button->GetId();
        }
    }
}
