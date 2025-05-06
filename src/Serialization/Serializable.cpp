#include "Serializable.h"

namespace shen
{
    Serializable::Serializable() = default;

    Serializable::Serializable(const Serializable& other)
    {
        if (this != &other)
        {
            ClearProperties();
        }
    }

    Serializable::Serializable(Serializable&& other) = default;

    Serializable::~Serializable() = default;

    Serializable& Serializable::operator = (const Serializable& other)
    {
        if (this != &other)
        {
            ClearProperties();
        }

        return *this;
    }

    Serializable& Serializable::operator = (Serializable&& other) = default;

    void Serializable::ClearProperties()
    {
        _fields.clear();
    }

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
