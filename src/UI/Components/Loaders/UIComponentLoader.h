#pragma once

#include "UI/UIWindowLoader.h"
#include "Registration/Registration.h"
#include <memory>

namespace shen
{
    class UINode;
    class UIComponent;
    class SystemsManager;
    class Serialization;

    class UIComponentLoader
    {
    public:
        virtual UIComponent* CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element) { return nullptr; }
    };
}
