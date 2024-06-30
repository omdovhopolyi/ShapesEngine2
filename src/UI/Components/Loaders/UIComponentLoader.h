#pragma once

#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class UINode;
    class UIComponent;
    class SystemsManager;

    class UIComponentLoader
    {
    public:
        UIComponentLoader(SystemsManager* systems);

        virtual UIComponent* Load(UINode* node, tinyxml2::XMLElement* element) = 0;

    protected:
        SystemsManager* _systems = nullptr;
    };
}
