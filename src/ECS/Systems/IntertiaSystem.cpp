#include "IntertiaSystem.h"

#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void IntertiaSystem::Update()
    {
        /*auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Mover>([&](auto entity, Mover& mover)
        {
            mover.velocity /= mover.inertia;
        });*/
    }
}
