#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Rect.hpp>

namespace shen
{
    class SerializableFieldFloatRect
        : public SerializableField
    {
    public:
        SerializableFieldFloatRect(sf::FloatRect& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::FloatRect& _field;
    };
}
