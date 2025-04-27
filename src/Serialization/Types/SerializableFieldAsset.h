#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    template<class T>
    class SerializableFieldAsset
        : public SerializableField
    {
    public:
        SerializableFieldAsset(std::shared_ptr<T>& field, const std::string& name)
            : SerializableField(name)
            , _field(field)
        {}

        void Load(const DataElementWrapper& element) override
        {
            if (auto childElement = element.GetChildElement(_name))
            {
                _field = std::make_shared<T>();
                _field->RegisterProperties();

                auto& fields = _field->GetFields();
                for (auto& field : fields)
                {
                    field->Load(*childElement);
                }
            }
        }

    public:
        std::shared_ptr<T>& _field;
    };
}
