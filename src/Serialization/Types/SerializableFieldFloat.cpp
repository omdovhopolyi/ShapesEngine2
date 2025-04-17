#include "SerializableFieldFloat.h"

namespace shen
{
    SerializableFieldFloat::SerializableFieldFloat(float& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    {}

    void SerializableFieldFloat::Load(const DataElementWrapper& element)
    {
        _field = element.GetFloat(_name);
    }
}
