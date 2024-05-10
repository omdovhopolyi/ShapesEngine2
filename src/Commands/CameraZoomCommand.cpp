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
                auto& world = context.systems->GetWorld();

                world.Each<Camera>([&](const auto entity, Camera& camera)
                {
                    auto zoom = 1.f - (*scrollVal * _speed);
                    camera.view.zoom(zoom);
                    camera.needUpdate = true;
                });
            }
        }
    }
}

