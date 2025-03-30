#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Rect.hpp>

namespace shen
{
    class SerializableFieldIntRect
        : public SerializableField
    {
    public:
        SerializableFieldIntRect(sf::IntRect& field, const std::string& name);
        void Load(const Serialization& element) override;

    private:
        sf::IntRect& _field;
    };
}
