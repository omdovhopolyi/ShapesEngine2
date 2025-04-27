#include "Serializable.h"

namespace shen
{
    Serializable::~Serializable() = default;

    std::vector<std::unique_ptr<SerializableField>>& Serializable::GetFields()
    {
        return _fields;
    }

    void Serializable::Save(DataElementWrapper& element)
    {
        // TODO
    }

    void Serializable::Load(const DataElementWrapper& element)
    {
        for (auto& field : GetFields())
        {
            field->Load(element);
        }
    }
}
