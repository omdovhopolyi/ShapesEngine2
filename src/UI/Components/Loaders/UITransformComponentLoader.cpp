#pragma once
#include "UITransformComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/UITransformComponent.h"
#include "Serialization/Serialization.h"

namespace shen
{
    UITransformComponentLoader::UITransformComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* UITransformComponentLoader::Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UITransformComponent>())
        {
            if (const auto idAttr = element->FindAttribute("id"))
            {
                const auto id = idAttr->Value();
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            auto transform = Serialization::LoadTransform(element);
            component->SetTransform(transform);
            return component.get();
        }

        return nullptr;
    }
}
