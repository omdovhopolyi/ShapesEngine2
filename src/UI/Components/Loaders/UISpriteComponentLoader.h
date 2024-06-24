#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UISpriteComponentLoader
        : public UIComponentLoader
    {
    public:
        UISpriteComponentLoader(SystemsManager* systems);

        void Load(UIComponent* component, tinyxml2::XMLElement* element) override;
    };
}
