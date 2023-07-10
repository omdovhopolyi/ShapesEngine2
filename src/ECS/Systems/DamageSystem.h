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

        void Subscribe();

        void Update() override;

    private:
        SubcriptionsContainer _subscriptions;
    };
}
