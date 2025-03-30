#include "SerializableFieldInt.h"

namespace shen
{
    SerializableFieldInt::SerializableFieldInt(int& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldInt::Load(const Serialization& element)
    {
        _field = element.GetInt(_name);
    }
}
