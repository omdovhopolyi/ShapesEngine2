#include "SerializableFieldTransform.h"

namespace shen
{
    SerializableFieldTransform::SerializableFieldTransform(sf::Transform& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldTransform::Load(const Serialization& element)
    {
        _field = element.GetTransform();
    }
}
