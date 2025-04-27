#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include "UI/UIWindow.h"
#include "Messenger/SubscriptionsContainer.h"
#include <vector>
#include <memory>
#include <string>

namespace shen
{
    class UIWindow;
    class UINode;
    class SystemsManager;
    class UIComponentLoader;
    class DataElementWrapper;

    class UIWindowLoader
        : public System
    {
        SYSTEMS_FACTORY(UIWindowLoader)

    public:
        void LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId);
        void LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, const DataElementWrapper& element);

        static std::string ComponentElementId;
        static std::string NodeElementId;
        static std::string TypeAttrId;
    };
}
