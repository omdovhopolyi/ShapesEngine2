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
        auto rb = world->GetComponent<RigidBody>(entity);
        const float speed = 50.f;
        rb->velocity += _direction;
        rb->velocity = glm::normalize(rb->velocity) * speed;
    }

    MoveUpCommand::MoveUpCommand()
        : MoveCommand(glm::vec3(0.f, -1.f, 0.f))
    { }

    MoveRightCommand::MoveRightCommand()
        : MoveCommand(glm::vec3(1.f, 0.f, 0.f))
    { }

    MoveDownCommand::MoveDownCommand()
        : MoveCommand(glm::vec3(0.f, 1.f, 0.f))
    { }

    MoveLeftCommand::MoveLeftCommand()
        : MoveCommand(glm::vec3(-1.f, 0.f, 0.f))
    { }
}
