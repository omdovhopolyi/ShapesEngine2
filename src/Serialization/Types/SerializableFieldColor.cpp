#include "SerializableFieldColor.h"

namespace shen
{
    SerializableFieldColor::SerializableFieldColor(sf::Color& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    {}

    void SerializableFieldColor::Load(const Serialization& element)
    {
        _field = element.GetColor(_name);
    }
}
