#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "Messenger/Events/Common.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class BaseInputSystem;

    class PlayerInputSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(PlayerInputSystem)

    public:
        void Init(SystemsManager* systems) override;
        void Start() override;
        void Update() override;

    private:
        void InitSubscriptions();
        void SetupInputSystems();

    private:
        std::vector<BaseInputSystem*> _inputSystems;
        SubcriptionsContainer _subscriptions;
    };
}
