#include "MovementSystem.h"
#include "ECS/EcsWorld.h"
#include "Game/Time.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Velocity.h"

namespace shen
{
    void MovementSystem::Update()
    {
        const auto dt = Time::Instance().Dt();

        EcsWorld::Instance().Each<Transform, Velocity>(
            [dt](const auto entity, auto& transform, const auto& velocity)
        {
            transform.position += velocity.velocity * dt;
        });
    }
}
