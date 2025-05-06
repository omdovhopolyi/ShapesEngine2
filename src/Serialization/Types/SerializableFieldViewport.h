#pragma once

#include "Serialization/SerializableField.h"
#include <SFML/Graphics/View.hpp>

namespace shen
{
    class SerializableFieldViewport
        : public SerializableField
    {
    public:
        SerializableFieldViewport(sf::View& field, const std::string& name);
        void Load(const DataElementWrapper& element) override;

    private:
        sf::View& _field;
    };
}
