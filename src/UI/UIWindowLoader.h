#pragma once

#include "Components/Loaders/UIComponentLoader.h"
#include <tinyxml2/tinyxml2.h>
#include <map>
#include <string>
#include <memory>

namespace shen
{
    class UIWindow;
    class UINode;
    class SystemsManager;

    class UIWindowLoader
    {
    public:
        UIWindowLoader(SystemsManager* systems);

        void LoadWindow(UIWindow* window, const std::string& windowId);
        void LoadNode(UIWindow* window, std::shared_ptr<UINode> node, tinyxml2::XMLElement* element);

    private:
        void RegisterComponentLoaders();
        UIComponentLoader* GetLoader(const std::string& type) const;

    private:
        SystemsManager* _systems = nullptr;
        std::map<std::string, std::unique_ptr<UIComponentLoader>> _loaders;
        int _nodeIdsCounter = 0;

        static std::string ComponentElementId;
        static std::string NodeElementId;
        static std::string TypeAttrId;
    };
}
