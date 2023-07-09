#pragma once

#include "System.h"

#include "Messenger/Messenger.h"

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
        std::shared_ptr<ISubscriptionWrapper> _subscription;
    };
}
