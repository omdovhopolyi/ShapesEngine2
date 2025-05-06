#include "RotateCommand.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Systems/TimeSystem.h"
#include "Logger/Logger.h"
#include "Utils/Coords.h"
#include "Utils/Math.h"

namespace shen
{
    REGISTER_LOADER(RotateCommand);

    void RotateCommand::Execute(const CommandContext& context) const
    {
        auto& time = context.systems->GetTime();
        if (time.IsGamePaused())
        {
            return;
        }

        auto& world = context.systems->GetWorld();

        auto renderTextures = context.systems->GetSystem<SfmlRenderTargetsSystem>();
        auto target = renderTextures->GetRenderTexture(SfmlRenderTargetsSystem::WorldTargetId); // TODO check target

        auto transform = world.GetOrCreateComponent<Transform>(context.entity);

        if (auto screenPos = context.vars.GetVar<sf::Vector2i>("pos"))
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
