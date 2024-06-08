#pragma once

#include "Command.h"

namespace shen
{
    class CameraZoomCommand
        : public Command
    {
    public:
        CameraZoomCommand() = default;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void Execute(const CommandContext& context) const override;

    protected:
        float _speed = 0.1f;
    };
}

