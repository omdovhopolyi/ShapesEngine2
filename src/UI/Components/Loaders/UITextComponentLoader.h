#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITextComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UITextComponent)

    public:
        UIComponent* CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element) override;
    };
}
