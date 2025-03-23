#pragma once

#include "Command.h"

namespace shen
{
    class PauseGameCommand
        : public Command
    {
    public:
        void Execute(const CommandContext& context) const override;
    };
}
