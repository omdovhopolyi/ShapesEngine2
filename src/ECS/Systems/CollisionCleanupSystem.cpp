#include "CollisionCleanupSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Physics.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(CollisionCleanupSystem)

    void CollisionCleanupSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.RemoveAllComponents<Collision>();
    }
}
