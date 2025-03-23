#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    class SerializableFieldString
        : public SerializableField
    {
    public:
        SerializableFieldString(std::string& field, const std::string& name);
        void Load(const Serialization& element) override;

    public:
        std::string& _field;
        std::string _name;
    };
}
