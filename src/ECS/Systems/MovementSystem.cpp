#include "MovementSystem.h"
#include "ECS/EcsWorld.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"

#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"

#include "Logger/Logger.h"

#include <box2d/box2d.h>

namespace shen
{
    void MovementSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Mover, RigidBody>(
            [&](const auto entity, Mover& mover, RigidBody& rb)
        {
            rb.body->ApplyForceToCenter({ mover.velocity.x, mover.velocity.y }, true);
        });
    }
}
