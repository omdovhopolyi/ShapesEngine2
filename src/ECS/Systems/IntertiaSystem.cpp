#include "IntertiaSystem.h"

#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void IntertiaSystem::Update()
    {
        /*auto& world = _systems->GetWorld();
        world.Each<Mover>([&](auto entity, Mover& mover)
        {
            mover.velocity /= mover.inertia;
        });*/
    }
}
