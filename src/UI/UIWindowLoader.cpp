#include "UIWindowLoader.h"
#include "UI/UIWindow.h"
#include "UINode.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
#include "Serialization/LoadersManager.h"
#include <format>

namespace shen
{
    std::string UIWindowLoader::ComponentElementId = "component";
    std::string UIWindowLoader::NodeElementId = "node";
    std::string UIWindowLoader::TypeAttrId = "type";

    void UIWindowLoader::LoadWindow(SystemsManager* systems, UIWindow* window, const std::string& windowId)
    {
        std::string path = FilePath::Path("assets/ui/") + windowId + ".xml";

        auto elementWrapper = XmlDataElementWrapper{ systems };
        elementWrapper.LoadFile(path);
        if (elementWrapper.IsValid())
        {
            auto root = window->GetOrCreateRoot();
            root->SetWindow(window);
            LoadNode(systems, window, root, elementWrapper);
            window->ResolveReferences();
            window->InitComponents();
        }
    }

    void UIWindowLoader::LoadNode(SystemsManager* systems, UIWindow* window, std::shared_ptr<UINode> node, const DataElementWrapper& element)
    {
        if (const auto& nodeId = node->GetId(); !nodeId.empty())
        {
            window->MapNode(nodeId, node);
        }

        element.ForAllChildren([&](const DataElementWrapper& element)
        {
            if (const auto type = element.GetStr("type"); !type.empty())
            {
                if (auto loader = LoadersManager::Instance().GetLoader(type))
                {
                    if (auto component = std::dynamic_pointer_cast<UIComponent>(loader->CreateAndLoad(element)))
                    {
                        component->SetNode(node.get());
                        component->AfterLoad();
                        component->RegisterReferences();
                        node->AddComponent(component);
                    }
                }
            }
        });

        element.ForAllChildren("node", [&](const DataElementWrapper& nodeElement)
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
