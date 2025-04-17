#pragma once

#include "Context/ContextBase.h"
#include "Utils/UsingPtrsMacro.h"
#include "Serialization/Serializable.h"

namespace shen
{
    class ConditionBase
        : public Serializable
    {
    public:
        USING_PTRS(ConditionBase);

        virtual ~ConditionBase() = default;

        virtual void Init() {};
        virtual bool Check(const ContextBase& context) const { return true; }
        virtual void Reset() {};
    };
}
