#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    template<class T>
    class SerializableFieldAssetsList
        : public SerializableField
    {
    public:
        SerializableFieldAssetsList(std::vector<std::shared_ptr<T>>& field, const std::string& name)
            : SerializableField(name)
            , _field(field)
        {
        }

        void Load(const DataElementWrapper& element) override
        {
            if (auto listElement = element.GetChildElement(_name))
            {
                listElement->ForAllChildren([](const DataElementWrapper& itemElement)
                {
                    _field = std::make_shared<T>();
                    _field->RegisterProperties();

                    auto& fields = _field->GetFields();
                    for (auto& field : fields)
                    {
                        field->Load(itemElement);
                    }
                });
            }
        }

    public:
        std::vector<std::shared_ptr<T>>& _field;
    };
}
