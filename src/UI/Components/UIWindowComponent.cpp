#include "UIWindowComponent.h"
#include "UI/UIWindow.h"

namespace shen
{
    REGISTER_CLASS_LOADER_TEST(UIWindowComponent)

    void UIWindowComponent::Close()
    {
        if (auto window = GetWindow())
        {
            window->Close();
        }
    }
}
