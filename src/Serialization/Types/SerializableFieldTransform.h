#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/Transform.hpp>

namespace shen
{
    class SerializableFieldTransform
        : public SerializableField
    {
    public:
        SerializableFieldTransform(sf::Transform& field, const std::string& name);
        void Load(const Serialization& element) override;

    private:
        sf::Transform& _field;
    };
}
