#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITransformComponentLoader
        : public UIComponentLoader
    {
    public:
        UITransformComponentLoader(SystemsManager* systems);

        UIComponent* Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
