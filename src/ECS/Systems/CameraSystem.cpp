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

        world->Each<Camera>([&](auto entity, Camera& camera)
        {
            camera.target.x = camera.position.x;
            camera.target.y = camera.position.y;

            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
            camera.projection = glm::perspective(glm::radians(camera.fov), 800.f / 640.f, camera.nearPlane, camera.farPlane);
        });
    }
}
