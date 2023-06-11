#include "MovementSystem.h"
#include "ECS/EcsWorld.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Velocity.h"

namespace shen
{
    void MovementSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Transform, Velocity>(
            [dt](const auto entity, auto& transform, const auto& velocity)
        {
            transform.position += velocity.velocity * dt;
        });
    }
}
