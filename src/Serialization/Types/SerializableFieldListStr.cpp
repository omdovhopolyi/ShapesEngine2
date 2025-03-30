#include "SerializableFieldListStr.h"

namespace shen
{
    SerializableFieldListStr::SerializableFieldListStr(std::vector<std::string>& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldListStr::Load(const Serialization& element)
    {
        _field = element.GetVecStr(_name);
    }
}
