#pragma once

#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class UIComponent;
    class SystemsManager;

    class UIComponentLoader
    {
    public:
        UIComponentLoader(SystemsManager* systems);

        virtual void Load(UIComponent* component, tinyxml2::XMLElement* element) = 0;

    protected:
        SystemsManager* _systems = nullptr;
    };
}
