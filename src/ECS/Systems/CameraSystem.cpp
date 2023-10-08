#include "CameraSystem.h"

#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

#include "Game/ManagersProvider.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace shen
{
    void CameraSystem::Update()
    {
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<CameraComp>(
            [&](auto entity, CameraComp& camera)
        {
            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
            camera.projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        });
    }
}
