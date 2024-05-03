#pragma once

#include "Command.h"

namespace shen
{
    class RotateCommand
        : public Command
    {
    public:
        void Execute(const Entity& entity, const CommandContext& context) const override;
    };
}
