#include "SerializableFieldIntRect.h"

namespace shen
{
    SerializableFieldIntRect::SerializableFieldIntRect(sf::IntRect& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldIntRect::Load(const DataElementWrapper& element)
    {
        _field = element.GetIntRect(_name);
    }
}
