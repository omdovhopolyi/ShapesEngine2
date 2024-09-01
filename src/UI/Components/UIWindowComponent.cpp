#include "UIWindowComponent.h"
#include "UI/UIWindow.h"

namespace shen
{
    void UIWindowComponent::Close()
    {
        if (auto window = GetWindow())
        {
            window->Close();
        }
    }
}
