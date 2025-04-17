#include "OrCondition.h"

namespace shen
{
    void OrCondition::RegisterProperties()
    {

    }

    bool OrCondition::Check(const ContextBase& context) const
    {
        bool result = true;

        for (const auto& condition : _conditions)
        {
            result |= condition->Check(context);
        }

        return result;
    }

    void OrCondition::AddCondition(const ConditionBase::Ptr& condition)
    {
        _conditions.push_back(condition);
    }
}
