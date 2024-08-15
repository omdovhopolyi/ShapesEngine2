#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITextComponentLoader
        : public UIComponentLoader
    {
        UI_COMPONENT_LOADER(UITextComponentLoader, UITextComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
