#pragma once

#include "Command.h"

namespace shen
{
    class PauseGameEventCommand
        : public Command
    {
    public:
        void Execute(const CommandContext& context) const override;
    };
}
