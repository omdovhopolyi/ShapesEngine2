#include "CameraFollowSystem.h"

#include "Game/ManagersProvider.h"
#include "Game/Camera.h"
#include "ECS/EcsWorld.h"

#include "ECS/Components/Common.h"

namespace shen
{
    void CameraFollowSystem::Update()
    {
        auto world = ManagersProvider::Instance().GetWorld();
        auto camera = ManagersProvider::Instance().GetCamera();

        world->Each<CameraTarget, Transform>(
            [&](auto entity, const Transform& transform)
        {
            camera->LookAt(transform.position);
        });
    }
}
