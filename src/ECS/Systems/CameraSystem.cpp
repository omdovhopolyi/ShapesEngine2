#include "CameraSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/View.hpp>

namespace shen
{
    void CameraSystem::Update()
    {
        auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetRenderWindow();
        auto& world = _systems->GetWorld();

        world.Each<Camera>([&](auto entity, Camera& camera)
        {
            if (camera.needUpdate)
            {
                camera.needUpdate = false;
                window->setView(camera.view);
            }
        });
    }
}
