#include "SerializableFieldListIntRect.h"

namespace shen
{
    SerializableFieldListIntRect::SerializableFieldListIntRect(std::vector<sf::IntRect>& field, const std::string& name, const std::string& itemId)
        : SerializableField(name)
        , _field(field)
        , _itemId(itemId)
    { }

    void SerializableFieldListIntRect::Load(const DataElementWrapper& element)
    {
        _field = element.GetVectorIntRect(_name, _itemId);
    }
}
