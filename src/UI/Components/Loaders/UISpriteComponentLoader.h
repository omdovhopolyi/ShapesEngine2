#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
    public:
        UISpriteComponentLoader(SystemsManager* systems);

        UIComponent* Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
