#pragma once

#include "Components/Loaders/UIComponentLoader.h"
#include "Utils/Singleton.h"
#include <tinyxml2/tinyxml2.h>
#include <map>
#include <string>
#include <memory>

namespace shen
{
    class UIWindow;
    class UINode;
    class SystemsManager;
    class UIComponentLoader;

    class UIWindowLoader
        : public Singleton<UIWindowLoader>
    {
    public:
        void LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId);
        void LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, tinyxml2::XMLElement* element);

        template<class T>
        void RegisterComponentLoader(const std::string& type);

    private:
        UIComponentLoader* GetLoader(const std::string& type) const;

    private:
        std::map<std::string, std::unique_ptr<UIComponentLoader>> _loaders;

        static std::string ComponentElementId;
        static std::string NodeElementId;
        static std::string TypeAttrId;
    };

    template<class T>
    void UIWindowLoader::RegisterComponentLoader(const std::string& type)
    {
        _loaders[type] = std::make_unique<T>();
    }
}
