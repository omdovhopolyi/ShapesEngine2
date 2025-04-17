#include "UIButtonComponentLoader.h"
#include "UI/Components/UIButtonComponent.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "Serialization/Serialization.h"
#include "Enums/ButtonSpriteEnum.h"
#include <string>

namespace shen
{
    /*REGISTER_CLASS_LOADER(UIButtonComponentLoader)

    UIComponent* UIButtonComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const DataElementWrapper& element)
    {
        if (auto component = node->AddComponent<UIButtonComponent>())
        {
            component->SetNode(node.get());

            auto sprites = systems->GetSystem<SfmlSpritesCollection>();

            if (const auto id = element.GetStr("id"); !id.empty())
            {
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapInputComponent(id, component);
                window->MapComponent(id, component);
            }

            element.ForAllChildren("sprite", [&](const DataElementWrapper& spriteElement)
            {
                auto type = ButtonSpriteTypeEnum.FromString(spriteElement.GetStr("type"));
                const auto spriteId = spriteElement.GetStr("sprite");
                auto sprite = sprites->GetSprite(spriteId);
                component->SetSprite(type, sprite);
            });

            const auto priority = element.GetInt("priority");
            component->SetInputPriority(priority);

            component->SetHoverSoundId(element.GetStr("sound_hover"));
            component->SetPressSoundId(element.GetStr("sound_press"));
            component->SetReleaseSoundId(element.GetStr("sound_release"));

            return component.get();
        }

        return nullptr;
    }*/
}
