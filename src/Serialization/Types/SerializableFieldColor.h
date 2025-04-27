#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Color.hpp>

namespace shen
{
    class SerializableFieldColor
        : public SerializableField
    {
    public:
        SerializableFieldColor(sf::Color& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::Color& _field;
    };
}
