#include "CameraZoomCommand.h"
#include "ECS/World.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Components/Common.h"
#include "Serialization/Types/SerializableFieldFloat.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraZoomCommand);

    void CameraZoomCommand::RegisterProperties()
    {
        Command::RegisterProperties();

        RegisterVar<SerializableFieldFloat>(_speed, "speed");
    }

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
        if (auto scrollVal = context.vars.GetVar<float>("var"))
        {
            auto& world = context.systems->GetWorld();

            world.Each<Camera>([&](const auto entity, Camera& camera)
            {
                auto zoom = 1.f - (*scrollVal * _speed);
                camera.view.zoom(zoom);
                camera.scale *= zoom;
                camera.needUpdate = true;
            });
        }
    }
}

