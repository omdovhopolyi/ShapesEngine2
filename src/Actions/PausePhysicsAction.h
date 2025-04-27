#pragma once

#include "Actions/ActionBase.h"

namespace shen
{
    class PausePhisicsAction
        : public ActionBase
    {
    public:
        PausePhisicsAction(bool pause = true);

        void RegisterProperties() override;

        void Execute(const ContextBase& context) const override;

    protected:
        bool _pause = true;
    };
}
