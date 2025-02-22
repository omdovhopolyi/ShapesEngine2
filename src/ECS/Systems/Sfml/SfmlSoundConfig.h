#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>

namespace shen
{
    class SfmlSoundConfig
        : public System
    {
        SYSTEMS_FACTORY(SfmlSoundConfig)

    public:
        void Load() override;
        void Stop() override;

        sf::Sound& GetSound(const std::string& id);
        sf::Music* GetMusic(const std::string& id);

        float GetSoundVolume() const { return _initialSoundVolume; }
        float GetMusicVolume() const { return _initialMusicVolume; }

    private:
        sf::SoundBuffer* GetResource(const std::string& id);

    private:
        std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
        std::unordered_map<std::string, sf::Sound> _sounds;
        std::unordered_map<std::string, sf::Music> _music;

        float _initialSoundVolume = 40.f;
        float _initialMusicVolume = 50.f;
    };
}
