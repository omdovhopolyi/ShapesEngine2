#pragma once

#include "Command.h"

namespace shen
{
    class PauseGameCommand
        : public Command
    {
        SERIALIZABLE(PauseGameCommand)

    public:
        void Execute(const CommandContext& context) const override;
    };
}
