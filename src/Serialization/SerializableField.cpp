#include "SerializableField.h"

namespace shen
{
    SerializableField::SerializableField(const std::string& name)
        : _name(name)
    {}

    SerializableField::~SerializableField() = default;
}
