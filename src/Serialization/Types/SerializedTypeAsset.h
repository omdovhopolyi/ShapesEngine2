#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    template<class T>
    class SerializableFieldAsset
        : public SerializableField
    {
    public:
        SerializableFieldAsset(std::shared_ptr<T>& field, const std::string& name) : _field(field), _name(name) {}

        void Load(const Serialization& element) override
        {
            if (auto childElement = element.GetElement(_name); childElement.IsElementValid())
            {
                _field = std::make_shared<T>();

                auto& fields = _field->GetFields();
                for (auto& field : fields)
                {
                    field->Load(childElement);
                }
            }
        }

    public:
        std::shared_ptr<T>& _field;
        std::string _name;
    };
}
