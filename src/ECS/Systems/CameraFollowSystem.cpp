#include "CameraFollowSystem.h"

#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void CameraFollowSystem::Update()
    {
        auto& world = _allSystems->GetWorld();

        world.Each<CameraTarget, Transform>(
            [&](auto entity, const Transform& transform)
        {
            //camera->LookAt(transform.position);
        });
    }
}
