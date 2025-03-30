#pragma once

#include <vector>
#include <memory>
#include <Serialization/Serialization.h>

namespace shen
{
    class SerializableField
    {
    public:
        SerializableField(const std::string& name);
        virtual ~SerializableField();

        virtual void Load(const Serialization&) {};
        virtual void Save(Serialization&) {}

    protected:
        std::string _name;
    };
}
