#pragma once

//#include "Serialization/Serializer.h"
#include <Utils/Singleton.h>
#include <map>
#include <string>
#include <memory>

namespace shen
{
    class UIWindow;
    class UINode;
    class SystemsManager;
    class UIComponentLoader;
    class DataElementWrapper;
    
    class UIWindowLoader
        : public Singleton<UIWindowLoader>
        //: public Serializer<UIComponentLoader, UIWindowLoader>
    {
    public:
        void LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId);
        void LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, const DataElementWrapper& element);

        static std::string ComponentElementId;
        static std::string NodeElementId;
        static std::string TypeAttrId;
    };
}
