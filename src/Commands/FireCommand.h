#pragma once

#include "Command.h"

namespace shen
{
    class FireCommand
        : public Command
    {
    public:
        void Execute(const Entity& entity) const override;
    };
}
