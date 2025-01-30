#include "UISpriteComponentLoader.h"
#include "UI/Components/UISpriteComponent.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "Serialization/Serialization.h"
#include <string>

namespace shen
{
    REGISTER_CLASS_LOADER(UISpriteComponentLoader)

    UIComponent* UISpriteComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element)
    {
        if (auto component = node->AddComponent<UISpriteComponent>())
        {
            component->SetNode(node.get());

            if (const auto id = element.GetStr("id"); !id.empty())
            {
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            const auto textureId = element.GetStr("texture");
            if (auto textures = systems->GetSystem<SfmlTexturesCollection>())
            {
                auto texture = textures->GetTexture(textureId);
                component->SetTexture(texture);
            }
            
            component->SetFillScreen(element.GetBool("fill"));

            auto color = element.GetColor("color");
            if (color != sf::Color::Transparent)
            {
                component->SetColor(color);
            }

            return component.get();
        }

        return nullptr;
    }
}
