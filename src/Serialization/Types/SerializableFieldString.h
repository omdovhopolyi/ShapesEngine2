#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    class SerializableFieldString
        : public SerializableField
    {
    public:
        SerializableFieldString(std::string& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        std::string& _field;
    };
}
