#include "CameraMouseMoveCommand.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    void CameraMouseMoveCommand::Execute(const CommandContext& context) const
    {
        auto renderTextures = context.systems->GetSystem<SfmlRenderTargetsSystem>();
        auto target = renderTextures->GetRenderTexture(SfmlRenderTargetsSystem::WorldTargetId); // TODO check target

        if (const auto screenDelta = context.GetVar<sf::Vector2i>("delta"))
        {
            auto& world = context.systems->GetWorld();
            world.Each<Camera>([&](const auto entity, Camera& camera)
            {
                camera.view.move(sf::Vector2f(-screenDelta->x / 2.f, -screenDelta->y / 2.f) * camera.scale);
                camera.needUpdate = true;
            });
        }
    }
}
