#include "SfmlSoundConfig.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void SfmlSoundConfig::Load()
    {
        const auto path = FilePath::Path("assets/configs/sounds.xml");
        auto serialization = Serialization{ _systems, path };
        serialization.SetupElement("sounds");
        serialization.ForAllChildElements("sound", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto soundPath = element.GetStr("path");

            sf::SoundBuffer buffer;
            if (buffer.loadFromFile(soundPath))
            {
                _sounds[id] = std::move(buffer);
            }
        });

        serialization.SetupElement("music");
        serialization.ForAllChildElements("track", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto trackPath = element.GetStr("path");

            auto& music = _music[id];
            const bool opened = music.openFromFile(trackPath);
            Assert(opened, std::format("[SfmlSoundConfig::Load] Cannot load music track {}", trackPath));
        });
    }

    sf::Sound SfmlSoundConfig::GetSound(const std::string& id) const
    {
        if (auto it = _sounds.find(id); it != _sounds.end())
        {
            return sf::Sound{ it->second };
        }

        return {};
    }

    sf::Music* SfmlSoundConfig::GetMusic(const std::string& id)
    {
        if (auto it = _music.find(id); it != _music.end())
        {
            return &it->second;
        }

        return nullptr;
    }
}
