#include "CameraMoveCommand.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Game/ManagersProvider.h"
#include "Game/Time.h"

namespace shen
{
    CameraMoveCommand::CameraMoveCommand(const glm::vec3& dir)
        : _direction(dir)
    {
    }

    void CameraMoveCommand::SetDirection(const glm::vec3& dir)
    {
        _direction = dir;
    }

    const glm::vec3 CameraMoveCommand::GetDirection() const
    {
        return _direction;
    }

    void CameraMoveCommand::SetSpeed(float speed)
    {
        _speed = speed;
    }

    float CameraMoveCommand::GetSpeed() const
    {
        return _speed;
    }

    void CameraMoveCommand::Execute(const Entity& entity, const CommandContext&) const
    {
        auto time = ManagersProvider::Instance().GetTime();

        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<Camera>([&](const auto entity, Camera& camera)
            {
                camera.position += (_direction * _speed * time->Dt());
            });
    }
}

