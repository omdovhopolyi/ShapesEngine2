#pragma once

#include "Serialization/SerializableField.h"
#include "UI/Components/UIComponent.h"

namespace shen
{
    template<class Ref>
    class SerializableFieldRef
        : public SerializableField
    {
    public:
        SerializableFieldRef(Ref& field, const std::string& name, const std::weak_ptr<UIComponent>& component)
            : SerializableField(name)
            , _field(field)
            , _component(component)
        { }

        void Load(const DataElementWrapper& element) override
        {
            if (auto component = _component.lock())
            {
                auto refElement = element.GetChildElement(_name);
                const auto compId = refElement->GetStr("compId");
                component->AddReferenceData(_name, compId);
                component->RegisterReference(_name, _field);
            }
        }

    private:
        Ref& _field;
        std::weak_ptr<UIComponent> _component;
    };
}
