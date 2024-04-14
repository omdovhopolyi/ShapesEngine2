#include "CameraSystem.h"

#include "ECS/World.h"
#include "ECS/Components/Common.h"

#include "Game/GameWindow.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace shen
{
    void CameraSystem::Start()
    {
        /*auto window = ManagersProvider::Instance().GetGameWindow();
        _viewportSize = { window->GetWidth(), window->GetHeight() };*/
    }

    void CameraSystem::Update()
    {
        /*auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Camera>([&](auto entity, Camera& camera)
        {
            camera.target.x = camera.position.x;
            camera.target.y = camera.position.y;

            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
            camera.projection = glm::perspective(glm::radians(camera.fov), _viewportSize.x / _viewportSize.y, camera.nearPlane, camera.farPlane);
        });*/
    }
}
