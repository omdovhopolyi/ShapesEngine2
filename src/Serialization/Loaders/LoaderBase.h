#pragma once

#include "Utils/Singleton.h"
#include "Serialization/Serializable.h"
#include <memory>

namespace shen
{
    class Serializable;

    class LoaderBase
    {
    public:
        ~LoaderBase() = default;
        virtual std::shared_ptr<Serializable> CreateAndLoad(const DataElementWrapper& serialization) = 0;
    };
}
