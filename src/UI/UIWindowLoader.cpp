#include "UIWindowLoader.h"
#include "UI/Components/Loaders/UIComponentLoader.h"
#include "UINode.h"
#include "Utils/Assert.h"
#include "UI/UIWindow.h"
#include <tinyxml2/tinyxml2.h>
#include <format>

namespace shen
{
    std::string UIWindowLoader::ComponentElementId = "component";
    std::string UIWindowLoader::NodeElementId = "node";
    std::string UIWindowLoader::TypeAttrId = "type";

    void UIWindowLoader::LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId)
    {
        tinyxml2::XMLDocument doc;

        std::string path = "../assets/ui/" + windowId + ".xml";

        const auto error = doc.LoadFile(path.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(false, std::format("[UIWindowLoader::LoadWindow] Can not load window '{}'", windowId));
            return;
        }

        if (auto rootElement = doc.FirstChildElement("root"))
        {
            auto root = window->GetOrCreateRoot();
            LoadNode(systems, window, root, rootElement);
            window->ResolveReferences();
            window->InitComponents();
        }
    }

    void UIWindowLoader::LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, tinyxml2::XMLElement* element)
    {
        if (const auto& nodeId = node->GetId(); !nodeId.empty())
        {
            window->MapNode(nodeId, node);
        }

        auto compElement = element->FirstChildElement(ComponentElementId.c_str());
        while (compElement)
        {
            if (const auto typeAttr = compElement->FindAttribute(TypeAttrId.c_str()))
            {
                const auto type = typeAttr->Value();

                if (auto loader = GetLoader(type))
                {
                    if (auto component = loader->Load(systems, node, compElement))
                    {
                        component->SetNode(node.get());
                        component->SetWindow(window);
                    }
                    else
                    {
                        Assert(false, std::format("Can not find ui component {}", type));
                    }
                }
            }

            compElement = compElement->NextSiblingElement();
        }

        auto childNodeElement = element->FirstChildElement(NodeElementId.c_str());
        while (childNodeElement)
        {
            std::string name;

            if (const auto nameAttr = childNodeElement->FindAttribute("name"))
            {
                name = nameAttr->Value();
            }
            
            auto child = node->AddChildPtr(name);
            child->SetWindow(window);

            if (const auto idAttr = childNodeElement->FindAttribute("id"))
            {
                child->SetId(idAttr->Value());
            }

            LoadNode(systems, window, child, childNodeElement);

            childNodeElement = childNodeElement->NextSiblingElement();
        }
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
