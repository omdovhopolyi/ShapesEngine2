#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace shen
{
    class SerializableFieldListIntRect
        : public SerializableField
    {
    public:
        SerializableFieldListIntRect(std::vector<sf::IntRect>& field, const std::string& name);
        void Load(const Serialization& element) override;

    private:
        std::vector<sf::IntRect>& _field;
    };
}
