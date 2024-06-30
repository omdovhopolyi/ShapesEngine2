#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITransformComponentLoader
        : public UIComponentLoader
    {
    public:
        UITransformComponentLoader(SystemsManager* systems);

        UIComponent* Load(UINode* node, tinyxml2::XMLElement* element) override;
    };
}
