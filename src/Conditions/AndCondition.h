#pragma once

#include "ConditionBase.h"
#include <vector>

namespace shen
{
    class AndCondition
        : public ConditionBase
    {
    public:
        void RegisterProperties() override;
        bool Check(const ContextBase& context) const;
        void AddCondition(const ConditionBase::Ptr& condition);

    protected:
        std::vector<ConditionBase::Ptr> _conditions;
    };
}
