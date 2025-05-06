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
        SerializableFieldListIntRect(std::vector<sf::IntRect>& field, const std::string& name, const std::string& itemId = "item");
        void Load(const DataElementWrapper& element) override;

    private:
        std::vector<sf::IntRect>& _field;
        std::string _itemId;
    };
}
