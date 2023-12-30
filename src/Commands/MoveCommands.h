#pragma once

#include "Command.h"
#include <glm/glm.hpp>
#include <memory>

namespace shen
{
    class MoveCommand
        : public Command
    {
    public:
        MoveCommand() = default;
        MoveCommand(const glm::vec3& dir);

        void SetDirection(const glm::vec3& dir);
        const glm::vec3 GetDirection() const;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void Execute(const Entity& entity, const CommandContext&) const override;

    protected:
        glm::vec3 _direction = glm::vec3{};
        float _speed = 1.f;
    };
}
