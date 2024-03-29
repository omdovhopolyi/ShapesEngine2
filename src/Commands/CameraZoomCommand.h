#pragma once

#include "Command.h"
#include <glm/glm.hpp>

namespace shen
{
    class CameraZoomCommand
        : public Command
    {
    public:
        CameraZoomCommand() = default;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void Execute(const Entity& entity, const CommandContext& context) const override;

    protected:
        float _speed = 1.f;
    };
}

