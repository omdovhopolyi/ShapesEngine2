#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace shen
{
    class SerializableFieldListStr
        : public SerializableField
    {
    public:
        SerializableFieldListStr(std::vector<std::string>& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        std::vector<std::string>& _field;
    };
}
