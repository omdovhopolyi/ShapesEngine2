#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Font.hpp>

namespace shen
{
    class SerializableFieldFont
        : public SerializableField
    {
    public:
        SerializableFieldFont(sf::Font& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::Font& _field;
    };
}
