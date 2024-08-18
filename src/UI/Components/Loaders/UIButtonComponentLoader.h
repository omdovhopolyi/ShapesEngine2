#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UIButtonComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UIButtonComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
