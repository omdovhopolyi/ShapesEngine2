#pragma once

#include "Context/ContextBase.h"
#include "Serialization/Serializable.h"

namespace shen
{
    class ActionBase
        : public Serializable
    {
    public:
        virtual ~ActionBase() = default;
        virtual void Execute(const ContextBase& context) const = 0;
    };
}
