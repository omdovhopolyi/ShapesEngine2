#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class WindowTestComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, WindowTestComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
