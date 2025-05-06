#include "SerializableFieldViewport.h"

namespace shen
{
    SerializableFieldViewport::SerializableFieldViewport(sf::View& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    {
    }

    void SerializableFieldViewport::Load(const DataElementWrapper& element)
    {
        _field.setCenter(element.GetVec2("position"));
        _field.setViewport(element.GetFloatRect("viewport", sf::FloatRect(0.f, 0.f, 1.f, 1.f)));
        _field.setRotation(element.GetFloat("rotation"));
        _field.setSize(element.GetVec2("size"));
    }
}
