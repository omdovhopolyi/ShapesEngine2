#include "UISpriteComponentLoader.h"
#include "UI/Components/UISpriteComponent.h"
#include "UI/UINode.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include <string>

namespace shen
{
    UISpriteComponentLoader::UISpriteComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* UISpriteComponentLoader::Load(UINode* node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UISpriteComponent>())
        {
            bool needFillScreen = false;
            std::string textureId;

            if (const auto fillScrAttr = element->FindAttribute("fillScreen"))
            {
                needFillScreen = fillScrAttr->BoolValue();
                component->SetFillScreen(needFillScreen);
            }

            if (const auto texAttr = element->FindAttribute("texture"))
            {
                textureId = texAttr->Value();
                auto textures = _systems->GetSystem<SfmlTexturesCollection>();
                auto texture = textures->GetTexture(textureId);
                component->SetTexture(texture);
            }

            return component;
        }

        return nullptr;
    }
}
