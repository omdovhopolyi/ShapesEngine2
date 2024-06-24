#include "UISpriteComponentLoader.h"
#include "UI/Components/UISpriteComponent.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include <string>

namespace shen
{
    UISpriteComponentLoader::UISpriteComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    void UISpriteComponentLoader::Load(UIComponent* component, tinyxml2::XMLElement* element)
    {
        auto spriteCompenent = static_cast<UISpriteComponent*>(component);

        bool needFillScreen = false;
        std::string textureId;

        if (const auto fillScrAttr = element->FindAttribute("fillScreen"))
        {
            needFillScreen = fillScrAttr->BoolValue();
            spriteCompenent->SetFillScreen(needFillScreen);
        }

        if (const auto texAttr = element->FindAttribute("texture"))
        {
            textureId = texAttr->Value();
            auto textures = _systems->GetSystem<SfmlTexturesCollection>();
            auto texture = textures->GetTexture(textureId);
            spriteCompenent->SetTexture(texture);
        }
    }
}
