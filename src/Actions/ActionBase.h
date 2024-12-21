#pragma once

#include "Context/ContextBase.h"

namespace shen
{
    class ActionBase
    {
    public:
        virtual void Execute(const ContextBase& context) const = 0;
    };
}
