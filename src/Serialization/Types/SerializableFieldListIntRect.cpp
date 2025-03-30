#include "SerializableFieldListIntRect.h"

namespace shen
{
    SerializableFieldListIntRect::SerializableFieldListIntRect(std::vector<sf::IntRect>& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldListIntRect::Load(const Serialization& element)
    {
        _field = element.GetVectorIntRect(_name);
    }
}
