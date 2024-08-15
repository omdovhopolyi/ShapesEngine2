#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
        UI_COMPONENT_LOADER(UISpriteComponentLoader, UISpriteComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
