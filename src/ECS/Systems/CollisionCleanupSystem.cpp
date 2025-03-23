#include "CollisionCleanupSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(CollisionCleanupSystem)

    void CollisionCleanupSystem::Update()
    {
        auto& world = _systems->GetWorld();

        if (auto physicsSystem = _systems->GetSystem<PhysicsBox2DSystem>())
        {
            world.Each<Destroy, RigidBody>([&](auto entity, RigidBody&)
            {
                physicsSystem->DestroyBody(entity);
            });
        }

        world.RemoveAllComponents<Collision>();
    }
}
