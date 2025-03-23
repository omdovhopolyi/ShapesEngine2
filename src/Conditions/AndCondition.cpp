#include "AndCondition.h"

namespace shen
{
    bool AndCondition::Check(const ContextBase& context) const
    {
        bool result = true;

        for (const auto& condition : _conditions)
        {
            result &= condition->Check(context);
        }

        return result;
    }

    void AndCondition::AddCondition(const ConditionBase::Ptr& condition)
    {
        _conditions.push_back(condition);
    }
}
