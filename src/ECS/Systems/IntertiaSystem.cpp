#include "IntertiaSystem.h"

#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void IntertiaSystem::Update()
    {
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<RigidBody>([&](auto entity, RigidBody& rb)
        {
            rb.velocity /= rb.inertia;
        });
    }
}
