#include "RotateCommand.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "Logger/Logger.h"
#include "Utils/Coords.h"
#include "Utils/Math.h"

namespace shen
{
    void RotateCommand::Execute(const CommandContext& context) const
    {
        auto& world = context.systems->GetWorld();

        auto renderTextures = context.systems->GetSystem<SfmlRenderTargetsSystem>();
        auto target = renderTextures->GetRenderTexture("world"); // TODO check target

        auto transform = world.GetOrCreateComponent<Transform>(context.entity);

        if (auto screenPos = context.GetVar<sf::Vector2i>("pos"))
        {
            auto worldPos = target->mapPixelToCoords(*screenPos);
            auto direction = worldPos - transform->position;
            direction = Normalize(direction);

            if (auto rotator = world.GetOrCreateComponent<Rotator>(context.entity))
            {
                rotator->rotation = Degrees(OrientedAngle(direction));
            }
        }
    }
}
