#include "CameraZoomCommand.h"
//#include "Game/ManagersProvider.h"
//#include "Game/Time.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void CameraZoomCommand::SetSpeed(float speed)
    {
        _speed = speed;
    }

    float CameraZoomCommand::GetSpeed() const
    {
        return _speed;
    }

    void CameraZoomCommand::Execute(const Entity& entity, const CommandContext& context) const
    {
        /*auto time = ManagersProvider::Instance().GetTime();

        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<Camera>([&](const auto entity, Camera& camera)
            {
                const auto dir = glm::normalize(glm::vec3{ 0.f, 0.f, -context.y });
                camera.position += (dir * _speed * time->Dt());
            });*/
    }
}

