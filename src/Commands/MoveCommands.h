#pragma once

#include "Command.h"
#include <glm/glm.hpp>

namespace shen
{
    class MoveCommand
        : public Command
    {
    public:
        MoveCommand(const glm::vec3& dir = glm::vec3{});

        void Execute(const Entity& entity) const override;

    protected:
        glm::vec3 _direction = glm::vec3{};
        float _speed = 50.f;
    };

    class MoveUpCommand
        : public MoveCommand
    {
    public:
        MoveUpCommand();
    };

    class MoveRightCommand
        : public MoveCommand
    {
    public:
        MoveRightCommand();
    };

    class MoveDownCommand
        : public MoveCommand
    {
    public:
        MoveDownCommand();
    };

    class MoveLeftCommand
        : public MoveCommand
    {
    public:
        MoveLeftCommand();
    };
}
