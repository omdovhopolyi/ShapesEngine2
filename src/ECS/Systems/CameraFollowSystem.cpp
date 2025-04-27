#include "CameraFollowSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(CameraFollowSystem)

    void CameraFollowSystem::Update()
    {
        auto& world = _systems->GetWorld();

        Camera* camera = nullptr;

        std::optional<sf::Vector2f> viewSize;

        world.Each<Camera>([&](const auto entity, Camera& cameraComp)
        {
            if (cameraComp.type == SfmlRenderTargetsSystem::WorldTargetId)
            {
                camera = &cameraComp;
            }
        });

        if (camera)
        {
            world.Each<CameraTarget, Transform>(
                [&](auto entity, const Transform& transform)
            {
                camera->view.setCenter(transform.position);
            });
        }
    }
}
