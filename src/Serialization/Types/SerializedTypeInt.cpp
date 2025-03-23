#include "SerializedTypeInt.h"
#include "Serialization/Serialization.h"

namespace shen
{
    SerializableFieldInt::SerializableFieldInt(int& field, const std::string& name)
        : _field(field)
        , _name(name)
    { }

    void SerializableFieldInt::Load(const Serialization& element)
    {
        _field = element.GetInt(_name);
    }
}
