#pragma once

#include "Command.h"

namespace shen
{
    class PauseGameEventCommand
        : public Command
    {
        SERIALIZABLE(PauseGameEventCommand)

    public:
        void Execute(const CommandContext& context) const override;
    };
}
