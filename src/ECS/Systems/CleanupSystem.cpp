#include "CleanupSystem.h"

#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void CleanupSystem::Update()
    {
        std::vector<Entity> toDestroy;

        auto& world = _systems->GetWorld();
        world.Each<Destroy>([&](auto entity)
        {
            toDestroy.push_back(entity);
        });

        for (auto& entity : toDestroy)
        {
            world.DestroyEntity(entity);
        }
    }
}
