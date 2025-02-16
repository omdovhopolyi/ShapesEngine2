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
        void Load() override;
        void Start() override;
        void Stop() override;

        void PlaySound(const std::string& id) const;
        void PlayMusic(const std::string& id) const;

        void StopMusic(const std::string& id) const;
        
        void SetSoundVolume(float volume);
        void SetMusicVolume(float volume);

    private:
        void InitSubscriptions();
        void ResetSubscriptions();

    private:
        float _soundVolume = 100.f;
        float _musicVolume = 100.f;

        SubcriptionsContainer _subscriptions;
    };
}
