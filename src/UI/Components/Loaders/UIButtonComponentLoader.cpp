#include "UIButtonComponentLoader.h"
#include "UI/Components/UIButtonComponent.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include <string>

namespace shen
{
    UIButtonComponentLoader::UIButtonComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* UIButtonComponentLoader::Load(UINode* node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UIButtonComponent>())
        {
            auto window = node->GetWindow();
            window->AddInputComponent(node->GetName(), component);

            auto sprites = _systems->GetSystem<SfmlSpritesCollection>();

            if (const auto spritesElement = element->FirstChildElement("sprites"))
            {
                if (const auto idleElem = spritesElement->FirstChildElement("idle"))
                {
                    if (const auto spriteAttr = idleElem->FindAttribute("sprite"))
                    {
                        const auto id = spriteAttr->Value();
                        auto sprite = sprites->GetSprite(id);
                        component->SetIdle(sprite);
                    }
                }

                if (const auto pressedElem = spritesElement->FirstChildElement("pressed"))
                {
                    if (const auto spriteAttr = pressedElem->FindAttribute("sprite"))
                    {
                        const auto id = spriteAttr->Value();
                        auto sprite = sprites->GetSprite(id);
                        component->SetPressed(sprite);
                    }
                }

                if (const auto hoverElem = spritesElement->FirstChildElement("hover"))
                {
                    if (const auto spriteAttr = hoverElem->FindAttribute("sprite"))
                    {
                        const auto id = spriteAttr->Value();
                        auto sprite = sprites->GetSprite(id);
                        component->SetHovered(sprite);
                    }
                }
            }

            if (const auto paramsElement = element->FirstChildElement("params"))
            {
                if (const auto priorityAttr = paramsElement->FindAttribute("priority"))
                {
                    const auto priority = priorityAttr->IntValue();
                    component->SetInputPriority(priority);
                }
            }

            return component.get();
        }

        return nullptr;
    }
}
