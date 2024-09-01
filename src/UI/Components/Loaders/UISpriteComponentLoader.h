#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UISpriteComponent)

    public:
        UIComponent* CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element) override;
    };
}
