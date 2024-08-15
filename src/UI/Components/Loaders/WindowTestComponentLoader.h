#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class WindowTestComponentLoader
        : public UIComponentLoader
    {
        UI_COMPONENT_LOADER(WindowTestComponentLoader, WindowTestComponent)

    public:
        UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) override;
    };
}
