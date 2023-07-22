#include "MovementSystem.h"
#include "ECS/EcsWorld.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"

#include "ECS/Components/Common.h"

namespace shen
{
    void MovementSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Transform, RigidBody>(
            [&](const auto entity, auto& transform, const auto& rigidBody)
        {
            transform.position += rigidBody.velocity * dt;
        });
    }
}
