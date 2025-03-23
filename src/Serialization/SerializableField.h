#pragma once

#include <vector>
#include <memory>
#include <Serialization/Serialization.h>

namespace shen
{
    class SerializableField
    {
    public:
        virtual ~SerializableField();
        virtual void Load(const Serialization& element) = 0;
    };
}
