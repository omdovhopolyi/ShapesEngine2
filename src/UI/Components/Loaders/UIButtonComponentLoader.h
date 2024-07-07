#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UIButtonComponentLoader
        : public UIComponentLoader
    {
    public:
        UIButtonComponentLoader(SystemsManager* systems);

        UIComponent* Load(UINode* node, tinyxml2::XMLElement* element) override;
    };
}
