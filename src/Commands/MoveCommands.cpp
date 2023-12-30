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
        if (auto rb = world->GetComponent<RigidBody>(entity))
        {
            rb->velocity += _direction;

            const auto result = glm::epsilonEqual(rb->velocity, glm::vec3{ 0.f }, std::numeric_limits<float>::epsilon());

            if (result != glm::bvec3{ true })
            {
                rb->direction = glm::normalize(rb->velocity);
            }

            rb->velocity = rb->direction * _speed;

            //Logger::Log("direcion x: {}, y: {}", rb->direction.x, rb->direction.y);
            //Logger::Log("velocity x: {}, y: {}", rb->velocity.x, rb->velocity.y);
        }
    }
}
