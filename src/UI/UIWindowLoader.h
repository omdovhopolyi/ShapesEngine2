#pragma once

#include "Serialization/Serializer.h"
#include <map>
#include <string>
#include <memory>

namespace tinyxml2
{
    class XMLElement;
}

namespace shen
{
    class UIWindow;
    class UINode;
    class SystemsManager;
    class UIComponentLoader;
    
    class UIWindowLoader
        : public Serializer<UIComponentLoader, UIWindowLoader>
    {
    public:
        void LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId);
        void LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, tinyxml2::XMLElement* element);

        static std::string ComponentElementId;
        static std::string NodeElementId;
        static std::string TypeAttrId;
    };
}
