#include "UITransformComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/UITransformComponent.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_CLASS_LOADER(UITransformComponentLoader)

    UIComponent* UITransformComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element)
    {
        if (auto component = node->AddComponent<UITransformComponent>())
        {
            component->SetNode(node.get());

            if (const auto id = element.GetStr("id"); !id.empty())
            {
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            component->SetTransform(element.GetTransform());

            return component.get();
        }

        return nullptr;
    }
}
