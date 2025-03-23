#include "SerializedTypeFloat.h"
#include "Serialization/Serialization.h"

namespace shen
{
    SerializableFieldFloat::SerializableFieldFloat(float& field, const std::string& name)
        : _field(field)
        , _name(name)
    {}

    void SerializableFieldFloat::Load(const Serialization& element)
    {
        _field = element.GetFloat(_name);
    }
}
