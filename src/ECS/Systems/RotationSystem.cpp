#include "RotationSystem.h"
#include "ECS/EcsWorld.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void RotationSystem::Update()
    {
        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<Rotator, Transform>([](const auto entity, const Rotator& rotator, Transform& transform)
        {
            transform.rotation = rotator.rotation;
        });
    }
}
