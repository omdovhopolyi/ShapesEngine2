#include "DamageSystem.h"
#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/CollisionEvent.h"

namespace shen
{
    DamageSystem::DamageSystem()
        : System()
    {
        Subscribe();
    }

    void DamageSystem::Subscribe()
    {
        _subscriptions.Subscribe<CollisionEvent>([this](const CollisionEvent& event)
        {
        });
    }

    void DamageSystem::Update()
    {
    }
}
