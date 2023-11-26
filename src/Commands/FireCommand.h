#pragma once

#include "Command.h"
#include <glm/glm.hpp>

namespace shen
{
    class FireCommand
        : public Command
    {
    public:
        void Execute(const Entity& entity, const CommandContext& context = {}) const override;

    private:
        float _bulletSpeed = 300.f;
    };
}
