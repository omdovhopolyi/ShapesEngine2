#include "UIWindowComponent.h"
#include "UI/UIWindow.h"

namespace shen
{
    void UIWindowComponent::Close()
    {
        _window->Close();
    }
}
