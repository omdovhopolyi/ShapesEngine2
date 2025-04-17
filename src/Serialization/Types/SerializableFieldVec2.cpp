#include "SerializableFieldVec2.h"

namespace shen
{
    SerializableFieldVec2::SerializableFieldVec2(sf::Vector2f& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldVec2::Load(const DataElementWrapper& element)
    {
        _field = element.GetVec2(_name);
    }
}
