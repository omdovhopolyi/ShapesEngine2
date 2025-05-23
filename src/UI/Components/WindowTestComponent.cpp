#include "WindowTestComponent.h"
#include "UI/UIWindow.h"

namespace shen
{
    REGISTER_LOADER(WindowTestComponent)

    void WindowTestComponent::RegisterReferences()
    {
        RegisterReference("testButton", _button);
    }

    void WindowTestComponent::Init()
    {
        if (auto button = _button.Get())
        {
            button->GetSignal().Subscribe(ButtonSignalType::Up, [this]()
            {
                Close();
            });
        }
    }
}
