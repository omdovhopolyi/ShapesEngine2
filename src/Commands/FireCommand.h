#pragma once

#include "Command.h"

namespace shen
{
    class FireCommand
        : public Command
    {
    public:
        void Execute(const CommandContext& context) const override;

    private:
        float _bulletSpeed = 300.f;
    };
}
