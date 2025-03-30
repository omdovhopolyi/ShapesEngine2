#pragma once

#include "Serialization/SerializableField.h"

namespace shen
{
    class SerializableFieldBool
        : public SerializableField
    {
    public:
        SerializableFieldBool(bool& field, const std::string& name);
        void Load(const Serialization& element) override;

    private:
        bool& _field;
    };
}
