#pragma once

#include "Command.h"
#include <glm/glm.hpp>

namespace shen
{
    class RotateCommand
        : public Command
    {
    public:
        void Execute(const Entity& entity, const CommandContext& context) const override;
    };
}
