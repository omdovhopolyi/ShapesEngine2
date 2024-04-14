#include "MovementSystem.h"
#include "ECS/World.h"
#include "Game/Time.h"

#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"

#include "Logger/Logger.h"

#include <box2d/box2d.h>

namespace shen
{
    void MovementSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();
        auto& world = _systems->GetWorld();
        auto time = _systems->GetSystem<TimeSystem>();

        world->Each<Mover, RigidBody>(
            [&](const auto entity, Mover& mover, RigidBody& rb)
        {
            auto force = b2Vec2(mover.velocity.x, mover.velocity.y);
            force *= dt;
            rb.body->ApplyForceToCenter(force, true);
        });
    }
}
