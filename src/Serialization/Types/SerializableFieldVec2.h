#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class SerializableFieldVec2
        : public SerializableField
    {
    public:
        SerializableFieldVec2(sf::Vector2f& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::Vector2f& _field;
    };
}
