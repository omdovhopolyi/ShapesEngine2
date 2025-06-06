#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    class SerializableFieldFloat
        : public SerializableField
    {
    public:
        SerializableFieldFloat(float& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    public:
        float& _field;
    };
}
