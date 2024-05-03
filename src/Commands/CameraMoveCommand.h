#pragma once

#include "Command.h"
//#include <glm/glm.hpp>
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class CameraMoveCommand
        : public Command
    {
    public:
        CameraMoveCommand() = default;
        CameraMoveCommand(const sf::Vector2f& dir);

        void SetDirection(const sf::Vector2f& dir);
        const sf::Vector2f& GetDirection() const;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void Execute(const Entity& entity, const CommandContext&) const override;

    protected:
        sf::Vector2f _direction;
        float _speed = 1.f;
    };
}

