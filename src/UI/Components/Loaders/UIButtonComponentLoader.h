#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UIButtonComponentLoader
        : public UIComponentLoader
    {
    public:
        UIButtonComponentLoader(SystemsManager* systems);

        UIComponent* Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
