#include "CameraMouseMoveCommand.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    REGISTER_CLASS_LOADER(CameraMouseMoveCommand);

    void CameraMouseMoveCommand::Execute(const CommandContext& context) const
    {
        if (auto renderTextures = context.systems->GetSystem<SfmlRenderTargetsSystem>())
        {
            if (auto target = renderTextures->GetRenderTexture(SfmlRenderTargetsSystem::WorldTargetId))
            {
                if (const auto screenDelta = context.vars.GetVar<sf::Vector2i>("delta"))
                {
                    auto& world = context.systems->GetWorld();
                    world.Each<Camera>([&](const auto entity, Camera& camera)
                    {
                        camera.view.move(sf::Vector2f(-screenDelta->x, -screenDelta->y) * camera.scale);
                        camera.needUpdate = true;
                    });
                }
            }
        }
    }
}
