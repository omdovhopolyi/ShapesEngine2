#pragma once

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
        UIComponentLoader(SystemsManager* systems);

        virtual UIComponent* Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element) = 0;

    protected:
        SystemsManager* _systems = nullptr;
    };
}
