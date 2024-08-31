#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class WindowTestComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, WindowTestComponent)

    public:
        UIComponent* CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element) override;
    };
}
