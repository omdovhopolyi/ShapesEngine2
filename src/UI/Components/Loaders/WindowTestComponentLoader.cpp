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
    WindowTestComponentLoader::WindowTestComponentLoader(SystemsManager* systems)
        : UIComponentLoader(systems)
    {}

    UIComponent* WindowTestComponentLoader::Load(const std::shared_ptr<UINode>& node, tinyxml2::XMLElement* element)
    {
        auto window = node->GetWindow();

        if (auto component = node->AddComponent<WindowTestComponent>())
        {
            component->SetWindow(window);

            if (const auto idAttr = element->FindAttribute("id"))
            {
                const auto id = idAttr->Value();
                component->SetId(id);
                auto window = node->GetWindow();
                window->MapComponent(id, component);
            }

            component->ClearReferencesData();

            auto refElem = element->FirstChildElement("ref");
            while (refElem)
            {
                const auto idAttr = refElem->FindAttribute("id");
                const auto compIdAttr = refElem->FindAttribute("compId");

                if (!idAttr || !compIdAttr)
                {
                    Assert(!idAttr, std::format("[WindowTestComponentLoader::Load] Incorrect ref for window {}", window->GetId()));
                    continue;
                }

                const auto id = idAttr->Value();
                const auto compId = compIdAttr->Value();

                component->AddReferenceData(id, compId);

                refElem = refElem->NextSiblingElement();
            }


            return component.get();
        }

        return nullptr;

    }
}
