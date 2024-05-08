#include "CameraZoomCommand.h"
#include "ECS/World.h"
#include "ECS/Systems/TimeSystem.h"
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

    void CameraZoomCommand::Execute(const CommandContext& context) const
    {
        if (auto it = context.vars.find("var"); it != context.vars.end())
        {
            if (auto scrollVal = std::any_cast<float>(&it->second))
            {
                auto& time = context.systems->GetTime();
                auto& world = context.systems->GetWorld();

                world.Each<Camera>([&](const auto entity, Camera& camera)
                {
                    const auto zoom = *scrollVal * _speed * time.Dt();
                    camera.view.zoom(zoom);
                    camera.needUpdate = true;
                });
            }
        }
    }
}

