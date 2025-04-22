#include "UIComponent.h"
#include "UI/UIWindow.h"
#include "Utils/Assert.h"
#include "Serialization/Types/SerializableFieldString.h"
#include <format>

namespace shen
{
    IUIComponentWrapper::~IUIComponentWrapper() = default;

    void UIComponent::RegisterProperties()
    {
        RegisterVar<SerializableFieldString>(_id, "id");
    }

    void UIComponent::AfterLoad()
    {
        if (!_id.empty())
        {
            auto window = GetWindow();
            window->MapComponent(_id, weak_from_this());
        }
    }

    UIComponent::~UIComponent() = default;

    UIWindow* UIComponent::GetWindow() const
    {
        if (_node)
        {
            return _node->GetWindow();
        }

        return nullptr;
    }

    void UIComponent::RegisterReference(const std::string& id, IUIComponentWrapper& component)
    {
        auto [it, isInserted] = _references.insert({ id, &component });
        //Assert(isInserted, std::format("Multiple references for id {} in window {}", id, GetWindow()->GetId()));
        Assert(isInserted, "[UIComponent::RegisterReference] Multiple references for id{} in window{}");
    } 

    void UIComponent::ClearReferencesData()
    {
        _refsMap.clear();
    }

    void UIComponent::AddReferenceData(const std::string& id, const std::string& compId)
    {
        const auto& [it, isInserted] = _refsMap.insert({ id, compId });
        //Assert(isInserted, std::format("[UIComponent::AddReferenceData] Multiple refs data in window {}", GetWindow()->GetId()));
        Assert(isInserted, "[UIComponent::AddReferenceData] Multiple refs data in window {}");
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

                if (auto window = GetWindow())
                {
                    if (auto component = window->GetComponent(refId); !component.expired())
                    {
                        ref->SetComponent(component);
                    }
                }
            }
        }
    }
}
