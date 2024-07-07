#include "UIWindowLoader.h"
#include "UINode.h"
#include "Components/Loaders/UITransformComponentLoader.h"
#include "Components/Loaders/UISpriteComponentLoader.h"
#include "Components/Loaders/UIButtonComponentLoader.h"
#include "Components/Loaders/UITextComponentLoader.h"
#include "Utils/Assert.h"
#include "UI/UIWindow.h"
#include <tinyxml2/tinyxml2.h>
#include <format>

namespace shen
{
    std::string UIWindowLoader::ComponentElementId = "component";
    std::string UIWindowLoader::NodeElementId = "node";
    std::string UIWindowLoader::TypeAttrId = "type";

    UIWindowLoader::UIWindowLoader(SystemsManager* systems)
        : _systems(systems)
    {
        RegisterComponentLoaders();
    }

    void UIWindowLoader::LoadWindow(UIWindow* window, const std::string& windowId)
    {
        tinyxml2::XMLDocument doc;

        std::string path = "../assets/ui/" + windowId + ".xml";

        const auto error = doc.LoadFile(path.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, std::format("[UIWindowLoader::LoadWindow] Can not load window '{}'", windowId));
            return;
        }

        if (auto rootElement = doc.FirstChildElement("root"))
        {
            auto root = window->GetOrCreateRoot();
            LoadNode(window, root, rootElement);
        }
    }

    void UIWindowLoader::LoadNode(UIWindow* window, UINode* node, tinyxml2::XMLElement* element)
    {
        auto compElement = element->FirstChildElement(ComponentElementId.c_str());
        while (compElement)
        {
            if (const auto typeAttr = compElement->FindAttribute(TypeAttrId.c_str()))
            {
                const auto type = typeAttr->Value();

                if (auto loader = GetLoader(type))
                {
                    if (auto component = loader->Load(node, compElement))
                    {
                        component->SetNode(node);
                        component->Init();
                    }
                    else
                    {
                        Assert(false, "Can not find ui component {}", type);
                    }
                }
            }

            compElement = compElement->NextSiblingElement();
        }

        auto childNodeElement = element->FirstChildElement(NodeElementId.c_str());
        while (childNodeElement)
        {
            auto child = node->AddChild("");
            child->SetWindow(window);

            LoadNode(window, child, childNodeElement);

            childNodeElement = childNodeElement->NextSiblingElement();
        }
    }

    void UIWindowLoader::RegisterComponentLoaders()
    {
        _loaders["transform"] = std::make_unique<UITransformComponentLoader>(_systems);
        _loaders["sprite"] = std::make_unique<UISpriteComponentLoader>(_systems);
        _loaders["button"] = std::make_unique<UIButtonComponentLoader>(_systems);
        _loaders["text"] = std::make_unique<UITextComponentLoader>(_systems);
    }

    UIComponentLoader* UIWindowLoader::GetLoader(const std::string& type) const
    {
        if (auto it = _loaders.find(type); it != _loaders.end())
        {
            return it->second.get();
        }
        return nullptr;
    }
}
