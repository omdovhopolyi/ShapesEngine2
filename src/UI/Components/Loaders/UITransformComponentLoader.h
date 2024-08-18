#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UITransformComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UITransformComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
