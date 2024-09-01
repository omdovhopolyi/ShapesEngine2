#include "WindowTestComponentLoader.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "UI/Components/WindowTestComponent.h"
#include "UI/Components/UIButtonComponent.h"
#include "Serialization/Serialization.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    REGISTER_CLASS_LOADER(WindowTestComponentLoader)

    UIComponent* WindowTestComponentLoader::CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element)
    {
        if (auto component = node->AddComponent<WindowTestComponent>())
        {
            component->SetNode(node.get());
            component->ClearReferencesData();

            if (const auto id = element.GetStr("id"); !id.empty())
            {
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            element.ForAllChildElements("refs", "ref", [&](const Serialization& refElement)
            {
                const auto id = refElement.GetStr("id");
                const auto compId = refElement.GetStr("compId");

                component->AddReferenceData(id, compId);
            });

            return component.get();
        }

        return nullptr;
    }
}
