#pragma once

#include "Serialization/SerializableField.h"
#include <set>

namespace shen
{
    class SerializableFieldSetStr
        : public SerializableField
    {
    public:
        SerializableFieldSetStr(std::set<std::string>& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        std::set<std::string>& _field;
    };
}
