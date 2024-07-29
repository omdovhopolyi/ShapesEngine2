#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class WindowTestComponentLoader
        : public UIComponentLoader
    {
    public:
        WindowTestComponentLoader(SystemsManager* systems);

        UIComponent* Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
