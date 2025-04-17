#include "SerializableFieldInt.h"

namespace shen
{
    SerializableFieldInt::SerializableFieldInt(int& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldInt::Load(const DataElementWrapper& element)
    {
        _field = element.GetInt(_name);
    }
}
