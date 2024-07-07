#include "UITextComponentLoader.h"
#include "UI/UINode.h"
#include "UI/Components/UITextComponent.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlFontsCollection.h"
#include "Serialization/Serialization.h"

namespace shen
{
    UITextComponentLoader::UITextComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* UITextComponentLoader::Load(UINode* node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UITextComponent>())
        {
            if (const auto textElement = element->FirstChildElement("text"))
            {
                if (const auto textAttr = textElement->FindAttribute("val"))
                {
                    const auto value = textAttr->Value();
                    component->SetText(value);
                }
            }

            if (const auto paramsElement = element->FirstChildElement("params"))
            {
                if (const auto fontAttr = paramsElement->FindAttribute("font"))
                {
                    const auto fontId = fontAttr->Value();
                    auto fonts = _systems->GetSystem<SfmlFontsCollection>();
                    if (const auto font = fonts->GetFont(fontId))
                    {
                        component->SetFont(*font);
                    }
                }

                const auto color = Serialization::LoadColor(paramsElement);
                component->SetColor(color);

                if (const auto sizeAttr = paramsElement->FindAttribute("size"))
                {
                    const auto fontSize = sizeAttr->IntValue();
                    component->SetSize(fontSize);
                }
            }

            return component;
        }

        return nullptr;
    }
}
