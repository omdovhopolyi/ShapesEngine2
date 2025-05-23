#include "CameraSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/View.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(CameraSystem)

    void CameraSystem::Update()
    {
        auto& world = _systems->GetWorld();
        auto renderTargets = _systems->GetSystem<SfmlRenderTargetsSystem>();
        auto worldTarget = renderTargets->GetRenderTexture(SfmlRenderTargetsSystem::WorldTargetId);

        world.Each<Camera>([&](auto entity, Camera& camera)
        {
            if (camera.needUpdate)
            {
                camera.needUpdate = false;
                worldTarget->setView(camera.view);
            }
        });
    }
}
