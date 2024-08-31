#include "UIWindowLoader.h"
#include "UI/Components/Loaders/UIComponentLoader.h"
#include "UI/UIWindow.h"
#include "UINode.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"
#include <format>

namespace shen
{
    std::string UIWindowLoader::ComponentElementId = "component";
    std::string UIWindowLoader::NodeElementId = "node";
    std::string UIWindowLoader::TypeAttrId = "type";

    void UIWindowLoader::LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId)
    {
        std::string path = "../assets/ui/" + windowId + ".xml";

        auto serialization = Serialization{ systems, path };
        if (serialization.IsValid())
        {
            serialization.SetupElement("root");
            auto root = window->GetOrCreateRoot();
            root->SetWindow(window);
            LoadNode(systems, window, root, serialization);
            window->ResolveReferences();
            window->InitComponents();
        }
    }

    void UIWindowLoader::LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, const Serialization& element)
    {
        if (const auto& nodeId = node->GetId(); !nodeId.empty())
        {
            window->MapNode(nodeId, node);
        }

        element.ForAllChildElements(ComponentElementId, [&](const Serialization& componentElement)
        {
            if (const auto type = componentElement.GetStr(TypeAttrId); !type.empty())
            {
                if (auto loader = GetLoader(type))
                {
                    if (auto component = loader->CreateAndLoad(systems, node, componentElement))
                    {
                        component->RegisterReferences();
                    }
                    else
                    {
                        Assert(false, std::format("Can not find ui component {}", type));
                    }
                }
            }
        });

        element.ForAllChildElements(NodeElementId, [&](const Serialization& nodeElement)
        {
            const auto name = nodeElement.GetStr("name");
            const auto id = nodeElement.GetStr("id");

            auto child = node->AddChildPtr(name);
            child->SetWindow(window);
            child->SetId(id);
            
            LoadNode(systems, window, child, nodeElement);
        });
    }
}
