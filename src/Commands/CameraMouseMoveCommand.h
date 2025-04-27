#pragma once

#include "Command.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class CameraMouseMoveCommand
        : public Command
    {
        SERIALIZABLE(CameraMouseMoveCommand)

    public:
        void Execute(const CommandContext& context) const override;
    };
}

