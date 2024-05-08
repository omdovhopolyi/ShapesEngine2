#include "MoveCommands.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "Logger/Logger.h"

namespace shen
{
    MoveCommand::MoveCommand(const sf::Vector2f& dir)
        : _direction(dir)
    { }

    void MoveCommand::SetDirection(const sf::Vector2f& dir)
    {
        _direction = dir;
    }

    const sf::Vector2f MoveCommand::GetDirection() const
    {
        return _direction;
    }

    void MoveCommand::SetSpeed(float speed)
    {
        _speed = speed;
    }

    float MoveCommand::GetSpeed() const
    {
        return _speed;
    }

    void MoveCommand::Execute(const CommandContext&) const
    {
        /*auto world = ManagersProvider::Instance().GetWorld();
        if (auto rb = world->GetComponent<Mover>(entity))
        {
            rb->velocity += _direction * _speed;
        }*/
    }
}
