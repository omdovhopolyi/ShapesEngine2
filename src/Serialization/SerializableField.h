#pragma once

#include <vector>
#include <memory>
#include <Serialization/DataElementWrapper.h>

namespace shen
{
    class SerializableField
    {
    public:
        SerializableField(const std::string& name);
        virtual ~SerializableField();

        virtual void Load(const DataElementWrapper&) {};
        virtual void Save(DataElementWrapper&) {}

    protected:
        std::string _name;
    };
}
