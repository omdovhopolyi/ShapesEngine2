#include "SerializableFieldString.h"

namespace shen
{
    SerializableFieldString::SerializableFieldString(std::string& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldString::Load(const Serialization& element)
    {
        _field = element.GetStr(_name);
    }
}
