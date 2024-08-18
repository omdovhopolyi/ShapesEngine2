#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UISpriteComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
