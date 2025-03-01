#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class SfmlSoundSystem
        : public System
    {
        SYSTEMS_FACTORY(SfmlSoundSystem)

    public:
        void Start() override;
        void Stop() override;

        void PlaySound(const std::string& id) const;
        void PlayMusic(const std::string& id) const;

        void StopMusic(const std::string& id) const;

    private:
        void InitSubscriptions();
        void ResetSubscriptions();

    private:
        SubcriptionsContainer _subscriptions;
    };
}
