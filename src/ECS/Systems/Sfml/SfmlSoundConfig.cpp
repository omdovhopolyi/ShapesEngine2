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

            auto buffer = GetResource(resourcePath);
            if (!buffer)
            {
                buffer = &(_soundBuffers[resourcePath]);
                const bool loaded = buffer->loadFromFile(resourcePath);
                Assert(loaded, std::format("[SfmlSoundConfig::Load] Cannot load sound resource {}", resourcePath));
            }

            _sounds[id] = sf::Sound{ *buffer };
        });

        serialization.SetupElement("music");
        serialization.ForAllChildElements("track", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto trackPath = FilePath::Path(element.GetStr("path"));

            auto& music = _music[id];
            const bool opened = music.openFromFile(trackPath);
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
