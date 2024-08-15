#pragma once

#include "UI/UIComponentRegistration.h"
#include <tinyxml2/tinyxml2.h>
#include <memory>

namespace shen
{
    class UINode;
    class UIComponent;
    class SystemsManager;

    class UIComponentLoader
    {
    public:
        UIComponentLoader();

        virtual UIComponent* Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) { return nullptr; }
    };
}
