#include "CameraMoveCommand.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/TimeSystem.h"

namespace shen
{
    CameraMoveCommand::CameraMoveCommand(const sf::Vector2f& dir)
        : _direction(dir)
    {
    }

    void CameraMoveCommand::SetDirection(const sf::Vector2f& dir)
    {
        _direction = dir;
    }

    const sf::Vector2f& CameraMoveCommand::GetDirection() const
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

    void CameraMoveCommand::Execute(const CommandContext& context) const
    {
        auto& world = context.systems->GetWorld();
        auto& time = context.systems->GetTime();

        world.Each<Camera>([&](const auto entity, Camera& camera)
        {
            const auto offset = _direction * _speed * time.Dt();
            camera.view.move(offset);
            camera.needUpdate = true;
        });
    }
}

