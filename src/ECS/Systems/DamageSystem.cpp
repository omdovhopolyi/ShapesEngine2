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
        _subscription = std::make_shared<SubscriptionWrapper<CollisionEvent>>([this](const CollisionEvent& event)
        {
            bool check = true;
        });

        ManagersProvider::Instance().GetMessenger()->Subscribe<CollisionEvent>(_subscription);
    }

    void DamageSystem::Update()
    {

    }
}
