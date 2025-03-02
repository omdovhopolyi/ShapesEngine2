#pragma once

#include "SfmlSoundSystem.h"
#include "SfmlSoundConfig.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlSoundConfig.h"
#include "Messenger/Events/Sounds.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlSoundSystem)

    void SfmlSoundSystem::Start()
    {
        InitSubscriptions();
    }

    void SfmlSoundSystem::Stop()
    {
        ResetSubscriptions();
    }

    void SfmlSoundSystem::PlaySound(const std::string& id) const
    {
        if (auto config = _systems->GetSystem<SfmlSoundConfig>())
        {
            auto& sound = config->GetSound(id);
            sound.play();
        }
    }

    void SfmlSoundSystem::PlayMusic(const std::string& id) const
    {
        if (auto config = _systems->GetSystem<SfmlSoundConfig>())
        {
            if (auto track = config->GetMusic(id))
            {
                track->play();
            }
        }
    }

    void SfmlSoundSystem::PauseMusic(const std::string& id) const
    {
        if (auto config = _systems->GetSystem<SfmlSoundConfig>())
        {
            if (auto track = config->GetMusic(id))
            {
                track->pause();
            }
        }
    }

    void SfmlSoundSystem::StopMusic(const std::string& id) const
    {
        if (auto config = _systems->GetSystem<SfmlSoundConfig>())
        {
            if (auto track = config->GetMusic(id))
            {
                track->stop();
            }
        }
    }

    void SfmlSoundSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<PlaySoundEvent>([this](const auto& event)
        {
            PlaySound(event.id);
        });

        _subscriptions.Subscribe<PlayMusicEvent>([this](const auto& event)
        {
            PlayMusic(event.id);
        });

        _subscriptions.Subscribe<PauseMusicEvent>([this](const auto& event)
        {
            PauseMusic(event.id);
        });

        _subscriptions.Subscribe<StopMusicEvent>([this](const auto& event)
        {
            StopMusic(event.id);
        });
    }

    void SfmlSoundSystem::ResetSubscriptions()
    {
        _subscriptions.Reset();
    }
}
