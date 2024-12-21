#pragma once

#include "Context/ContextBase.h"
#include "Utils/UsingPtrsMacro.h"

namespace shen
{
    class ConditionBase
    {
    public:
        USING_PTRS(ConditionBase);

        virtual void Init() {};
        virtual bool Check(const ContextBase& context) const { return true; }
        virtual void Reset() {};
    };
}
