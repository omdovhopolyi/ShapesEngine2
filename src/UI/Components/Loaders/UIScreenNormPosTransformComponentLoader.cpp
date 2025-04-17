#include "UIScreenNormPosTransformComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/UIScreenNormPosTransformComponent.h"
#include "Serialization/Serialization.h"

namespace shen
{
    /*REGISTER_CLASS_LOADER(UIScreenNormPosTransformComponentLoader)

    UIComponent* UIScreenNormPosTransformComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const DataElementWrapper& element)
    {
        if (auto component = node->AddComponent<UIScreenNormPosTransformComponent>())
        {
            component->SetNode(node.get());

            if (const auto id = element.GetStr("id"); !id.empty())
            {
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            component->SetNormPosition(element.GetVec2("position"));
            component->SetAngle(element.GetFloat("rotation"));
            component->SetScale(element.GetVec2("scale", { 1.f, 1.f }));
            component->SetAnchor(element.GetVec2("anchor"));

            return component.get();
        }

        return nullptr;
    }*/
}
