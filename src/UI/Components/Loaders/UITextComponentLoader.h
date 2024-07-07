#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITextComponentLoader
        : public UIComponentLoader
    {
    public:
        UITextComponentLoader(SystemsManager* systems);

        UIComponent* Load(UINode* node, tinyxml2::XMLElement* element) override;
    };
}
