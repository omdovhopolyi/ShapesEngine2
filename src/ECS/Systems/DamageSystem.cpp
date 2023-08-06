#include "DamageSystem.h"
#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/CollisionEvent.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

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
            ProcessBulletHit(event.a, event.b);
        });
    }

    bool DamageSystem::ProcessBulletHit(Entity a, Entity b) const
    {
        auto world = ManagersProvider::Instance().GetWorld();

        auto process = [&](auto bulletEnt, auto targetEnt)
        {
            if (auto bullet = world->GetComponent<Bullet>(bulletEnt))
            {
                if (bullet->owner != targetEnt)
                {
                    if (auto health = world->GetComponent<Health>(targetEnt))
                    {
                        health->amount -= bullet->damage;

                        if (health->amount <= 0)
                        {
                            world->AddComponent<Destroy>(targetEnt);
                        }
                    }
                    else
                    {
                        world->AddComponent<Destroy>(targetEnt);
                    }

                    world->AddComponent<Destroy>(bulletEnt);
                }
            }
        };

        if (auto bullet = world->GetComponent<Bullet>(a))
        {
            process(a, b);
            return true;
        }

        if (auto bullet = world->GetComponent<Bullet>(b))
        {
            process(b, a);
            return true;
        }

        return false;
    }
}
