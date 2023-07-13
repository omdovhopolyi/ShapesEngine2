#pragma once

#include "System.h"

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
        SubcriptionsContainer _subscriptions;
    };
}
