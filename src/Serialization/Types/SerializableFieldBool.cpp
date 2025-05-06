#include "SerializableFieldBool.h"

namespace shen
{
    SerializableFieldBool::SerializableFieldBool(bool& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    {}

    void SerializableFieldBool::Load(const DataElementWrapper& element)
    {
        _field = element.GetBool(_name, _field);
    }
}
