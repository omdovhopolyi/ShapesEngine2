#pragma once

#include "Command.h"
//#include <glm/glm.hpp>
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class MoveCommand
        : public Command
    {
    public:
        MoveCommand() = default;
        MoveCommand(const sf::Vector2f& dir);

        void SetDirection(const sf::Vector2f& dir);
        const sf::Vector2f GetDirection() const;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void Execute(const CommandContext&) const override;

    protected:
        sf::Vector2f _direction;
        float _speed = 1.f;
    };
}
