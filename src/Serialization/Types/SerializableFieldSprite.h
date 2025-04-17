#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

namespace shen
{
    class SerializableFieldSprite
        : public SerializableField
    {
    public:
        SerializableFieldSprite(sf::Sprite& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::Sprite& _field;
    };
}
