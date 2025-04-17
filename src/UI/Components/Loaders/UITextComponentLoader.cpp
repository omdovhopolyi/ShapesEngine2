#include "UITextComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/UITextComponent.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlFontsCollection.h"
#include "Serialization/Serialization.h"

namespace shen
{
    //REGISTER_CLASS_LOADER(UITextComponentLoader)

    //UIComponent* UITextComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const DataElementWrapper& element)
    //{
    //    if (auto component = node->AddComponent<UITextComponent>())
    //    {
    //        component->SetNode(node.get());

    //        if (const auto id = element.GetStr("id"); !id.empty())
    //        {
    //            component->SetId(id);
    //            auto window = node->GetWindow();
    //            window->MapComponent(id, component);
    //        }
    //        
    //        const auto text = element.GetStr("text");
    //        component->SetText(text);

    //        auto str = component->GetText();

    //        const auto fontId = element.GetStr("font");
    //        if (auto fonts = systems->GetSystem<SfmlFontsCollection>())
    //        {
    //            if (const auto font = fonts->GetFont(fontId))
    //            {
    //                component->SetFont(*font);
    //            }
    //        }

    //        const auto defaultColor = component->GetColor();
    //        const auto color = element.GetColor("color", defaultColor);
    //        component->SetColor(color);

    //        const auto defaultSize = component->GetSize();
    //        const auto fontSize = element.GetInt("size", defaultSize);
    //        component->SetSize(fontSize);

    //        const auto defaultSpacing = component->GetSpacing();
    //        const auto spacing = element.GetInt("letterSpace", defaultSpacing);
    //        component->SetSpacing(spacing);

    //        return component.get();
    //    }

    //    return nullptr;
    //}
}
