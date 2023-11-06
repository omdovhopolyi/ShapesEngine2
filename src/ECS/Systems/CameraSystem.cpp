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

        world->Each<Camera>(
            [&](auto entity, Camera& camera)
        {
            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
            camera.projection = glm::perspective(glm::radians(camera.fov), 800.f / 640.f, 0.1f, 1000.0f);
            //camera.projection = glm::ortho(0.0f, 800.0f, 640.0f, 0.f, -100.f, 100.0f);
        });
    }
}
