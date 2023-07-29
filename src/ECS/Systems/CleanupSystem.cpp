#include "CleanupSystem.h"

#include "System.h"
#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void CleanupSystem::Update()
    {
        auto world = ManagersProvider::Instance().GetWorld();

        std::vector<Entity> toDestroy;

        world->Each<Destroy>([&](auto entity)
        {
            toDestroy.push_back(entity);
        });

        for (auto& entity : toDestroy)
        {
            world->DestroyEntity(entity);
        }
    }
}
