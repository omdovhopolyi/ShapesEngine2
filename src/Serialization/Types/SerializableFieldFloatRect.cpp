#include "SerializableFieldFloatRect.h"

namespace shen
{
    SerializableFieldFloatRect::SerializableFieldFloatRect(sf::FloatRect& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }
    
    void SerializableFieldFloatRect::Load(const DataElementWrapper& element)
    {
        _field = element.GetFloatRect(_name);
    }
}
