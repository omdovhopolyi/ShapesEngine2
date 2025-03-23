#include "SerializedTypeString.h"
#include "Serialization/Serialization.h"

namespace shen
{
    SerializableFieldString::SerializableFieldString(std::string& field, const std::string& name)
        : _field(field)
        , _name(name)
    {
    }

    void SerializableFieldString::Load(const Serialization& element)
    {
        _field = element.GetStr(_name);
    }
}
