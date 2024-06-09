#include "CameraSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/View.hpp>

namespace shen
{
    void CameraSystem::Update()
    {
        auto& world = _systems->GetWorld();
        auto renderTargets = _systems->GetSystem<SfmlRenderTargetsSystem>();
        auto worldTarget = renderTargets->GetRenderTexture("world");

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
