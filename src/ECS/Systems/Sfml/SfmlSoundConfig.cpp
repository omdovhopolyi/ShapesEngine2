#include "SfmlSoundConfig.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlSoundConfig)

    void SfmlSoundConfig::Load()
    {
        const auto path = FilePath::Path("assets/configs/sounds.xml");
        auto serialization = Serialization{ _systems, path };

        serialization.SetupElement("sounds");
        serialization.ForAllChildElements("sound", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto resourcePath = FilePath::Path(element.GetStr("path"));
            const auto volume = element.GetFloat("volume", _defaultSoundVolume);

            auto buffer = GetResource(resourcePath);
            if (!buffer)
            {
                buffer = &(_soundBuffers[resourcePath]);
                const bool loaded = buffer->loadFromFile(resourcePath);
                Assert(loaded, std::format("[SfmlSoundConfig::Load] Cannot load sound resource {}", resourcePath));
            }

            auto sound = sf::Sound{ *buffer };
            sound.setVolume(volume);
            _sounds[id] = sound;
        });

        serialization.SetupElement("music");
        serialization.ForAllChildElements("track", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto trackPath = FilePath::Path(element.GetStr("path"));
            const bool isLoop = element.GetBool("loop");
            const auto volume = element.GetFloat("volume", _defaultMusicVolume);

            auto& music = _music[id];
            music.setVolume(volume);
            const bool opened = music.openFromFile(trackPath);
            music.setLoop(isLoop);
            Assert(opened, std::format("[SfmlSoundConfig::Load] Cannot load music track {}", trackPath));
        });
    }

    void SfmlSoundConfig::Stop()
    {
        _sounds.clear();
        _music.clear();
    }

    sf::Sound& SfmlSoundConfig::GetSound(const std::string& id)
    {
        if (auto it = _sounds.find(id); it != _sounds.end())
        {
            return it->second;
        }

        static sf::Sound empty;
        return empty;
    }

    sf::Music* SfmlSoundConfig::GetMusic(const std::string& id)
    {
        if (auto it = _music.find(id); it != _music.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    sf::SoundBuffer* SfmlSoundConfig::GetResource(const std::string& id)
    {
        if (auto it = _soundBuffers.find(id); it != _soundBuffers.end())
        {
            return &it->second;
        }

        return nullptr;
    }
}
