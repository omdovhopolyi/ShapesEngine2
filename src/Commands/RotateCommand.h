#pragma once

#include "Command.h"

namespace shen
{
    class RotateCommand
        : public Command
    {
    public:
        void Execute(const CommandContext& context) const override;
    };
}
