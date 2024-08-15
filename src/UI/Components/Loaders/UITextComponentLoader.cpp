#include "UITextComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/UITextComponent.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlFontsCollection.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_UI_COMPONENT_LOADER(UITextComponentLoader)

    UIComponent* UITextComponentLoader::Load(SystemsManager* systems, const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element)
    {
        if (auto component = node->AddComponent<UITextComponent>())
        {
            if (const auto idAttr = element->FindAttribute("id"))
            {
                const auto id = idAttr->Value();
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

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
                    auto fonts = systems->GetSystem<SfmlFontsCollection>();
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

            return component.get();
        }

        return nullptr;
    }
}
