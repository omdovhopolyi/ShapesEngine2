#pragma once

#include "Actions/ActionBase.h"

namespace shen
{
    class ResetPhisicsAccumulatedTimeAction
        : public ActionBase
    {
    public:
        void Execute(const ContextBase& context) const override;
    };
}
