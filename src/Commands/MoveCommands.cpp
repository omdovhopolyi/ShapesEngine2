#include "MoveCommands.h"

#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Logger/Logger.h"

namespace shen
{
    MoveCommand::MoveCommand(const glm::vec3& dir)
        : _direction(dir)
    { }

    void MoveCommand::SetDirection(const glm::vec3& dir)
    {
        _direction = dir;
    }

    const glm::vec3 MoveCommand::GetDirection() const
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

    void MoveCommand::Execute(const Entity& entity, const CommandContext&) const
    {
        auto world = ManagersProvider::Instance().GetWorld();
        if (auto rb = world->GetComponent<Mover>(entity))
        {
            rb->velocity += _direction * _speed;
        }
    }
}
