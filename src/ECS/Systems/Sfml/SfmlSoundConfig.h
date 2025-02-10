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
    public:
        void Load() override;

        sf::Sound GetSound(const std::string& id) const;
        sf::Music* GetMusic(const std::string& id);

    private:
        std::map<std::string, sf::SoundBuffer> _sounds;
        std::map<std::string, sf::Music> _music;
    };
}
