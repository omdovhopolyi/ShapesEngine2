#include "DamageSystem.h"
#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/CollisionEvent.h"
#include "ECS/EcsWorld.h"

namespace shen
{
    DamageSystem::DamageSystem()
        : System()
    {
    }

    void DamageSystem::Start()
    {
        Subscribe();
        // TODO clear subscriptions on stop
    }

    void DamageSystem::Update()
    {
    }

    void DamageSystem::Subscribe()
    {
        _subscriptions.Subscribe<CollisionEvent>([this](const CollisionEvent& event)
        {
            auto world = ManagersProvider::Instance().GetWorld();

            world->DestroyEntity(event.a);
            world->DestroyEntity(event.b);
        });
    }
}
