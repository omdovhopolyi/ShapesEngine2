#include "UISpriteComponentLoader.h"
#include "UI/Components/UISpriteComponent.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include <string>

namespace shen
{
    REGISTER_CLASS_LOADER(UISpriteComponentLoader)

    UIComponent* UISpriteComponentLoader::Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UISpriteComponent>())
        {
            bool needFillScreen = false;
            std::string textureId;

            if (const auto idAttr = element->FindAttribute("id"))
            {
                const auto id = idAttr->Value();
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            if (const auto texElement = element->FirstChildElement("texture"))
            {
                if (const auto texAttr = texElement->FindAttribute("val"))
                {
                    const auto textureId = texAttr->Value();
                    auto textures = systems->GetSystem<SfmlTexturesCollection>();
                    auto texture = textures->GetTexture(textureId);
                    component->SetTexture(texture);
                }   
            }

            if (const auto paramsElement = element->FirstChildElement("params"))
            {
                if (const auto fillAttr = paramsElement->FindAttribute("fill"))
                {
                    component->SetFillScreen(fillAttr->BoolValue());
                }
            }

            return component.get();
        }

        return nullptr;
    }
}
