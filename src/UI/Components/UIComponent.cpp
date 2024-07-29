#include "UIComponent.h"
#include "UI/UIWindow.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    void UIComponent::RegisterReference(const std::string& id, std::weak_ptr<UIComponent>* component)
    {
        auto [it, isInserted] = _references.insert({ id, component });
        if (!isInserted)
        {
            Assert(false, std::format("Multiple references for id {} in window {}", id, _window->GetId()));
        }
    }

    void UIComponent::ClearReferencesData()
    {
        _refsMap.clear();
    }

    void UIComponent::AddReferenceData(const std::string& id, const std::string& compId)
    {
        const auto& [it, isInserted] = _refsMap.insert({ id, compId });
        Assert(isInserted, std::format("[UIComponent::AddReferenceData] Multiple refs data in window {}", _window->GetId()));
    }

    const std::string& UIComponent::GetReferenceData(const std::string& id) const
    {
        if (auto it = _refsMap.find(id); it != _refsMap.end())
        {
            return it->second;
        }

        static std::string empty;
        return empty;
    }

    void UIComponent::ResolveReferences()
    {
        for (auto& [id, ref] : _references)
        {
            if (auto it = _refsMap.find(id); it != _refsMap.end())
            {
                const auto refId = it->second;

                if (auto component = _window->GetComponent(refId); !component.expired())
                {
                    *ref = component;
                }
            }
        }
    }
}
