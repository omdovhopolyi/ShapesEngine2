#include "RotateCommand.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "Logger/Logger.h"
#include "Utils/Coords.h"
#include "Utils/Math.h"

namespace shen
{
    void RotateCommand::Execute(const CommandContext& context) const
    {
        auto& world = context.systems->GetWorld();
        auto windowSystem = context.systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetRenderWindow();

        auto transform = world.GetOrCreateComponent<Transform>(context.entity);

        if (auto screenPos = context.GetVar<sf::Vector2i>("pos"))
        {
            auto worldPos = window->mapPixelToCoords(*screenPos);
            auto direction = worldPos - transform->position;
            direction = Normalize(direction);

            if (auto rotator = world.GetOrCreateComponent<Rotator>(context.entity))
            {
                rotator->rotation = Degrees(OrientedAngle(direction));
            }
        }
    }
}
