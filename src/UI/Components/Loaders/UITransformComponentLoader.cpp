#pragma once
#include "UITransformComponentLoader.h"
#include "UI/UINode.h"
#include "UI/Components/UITransformComponent.h"
#include "Serialization/Serialization.h"

namespace shen
{
    UITransformComponentLoader::UITransformComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* UITransformComponentLoader::Load(UINode* node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UITransformComponent>())
        {
            auto transform = Serialization::LoadTransform(element);
            component->SetTransform(transform);
            return component;
        }

        return nullptr;
    }
}
