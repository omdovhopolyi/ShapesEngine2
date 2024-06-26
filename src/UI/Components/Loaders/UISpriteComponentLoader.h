#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
    public:
        UISpriteComponentLoader(SystemsManager* systems);

        UIComponent* Load(UINode* node, tinyxml2::XMLElement* element) override;
    };
}
