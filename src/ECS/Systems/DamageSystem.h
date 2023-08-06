#pragma once

#include "System.h"
#include "ECS/Entity.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class DamageSystem
        : public System
    {
    public:
        DamageSystem();

        void Start() override;
        void Update() override;

        void Subscribe();

    private:
        bool ProcessBulletHit(Entity a, Entity b) const;

    private:
        SubcriptionsContainer _subscriptions;
    };
}
