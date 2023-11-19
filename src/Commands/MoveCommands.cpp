#include "MoveCommands.h"

#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    MoveCommand::MoveCommand(const glm::vec3& dir/* = glm::vec2{}*/)
        : _direction(dir)
    { }

    void MoveCommand::Execute(const Entity& entity) const
    {
        auto world = ManagersProvider::Instance().GetWorld();
        if (auto rb = world->GetComponent<RigidBody>(entity))
        {
            rb->velocity += _direction;
            rb->direction = glm::normalize(rb->velocity);
            rb->velocity = rb->direction * _speed;
        }
    }

    MoveUpCommand::MoveUpCommand()
        : MoveCommand(glm::vec3(0.f, 1.f, 0.f))
    { }

    MoveRightCommand::MoveRightCommand()
        : MoveCommand(glm::vec3(1.f, 0.f, 0.f))
    { }

    MoveDownCommand::MoveDownCommand()
        : MoveCommand(glm::vec3(0.f, -1.f, 0.f))
    { }

    MoveLeftCommand::MoveLeftCommand()
        : MoveCommand(glm::vec3(-1.f, 0.f, 0.f))
    { }
}
