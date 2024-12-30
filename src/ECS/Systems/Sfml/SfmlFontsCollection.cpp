#include "SfmlFontsCollection.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlFontsCollection)

    void SfmlFontsCollection::Start()
    {
        LoadFontsPaths(FilePath::Path("assets/configs/fonts.xml"));
    }

    void SfmlFontsCollection::Stop()
    {
        _fonts.clear();
    }

    void SfmlFontsCollection::LoadFonts()
    {
        for (const auto& [id, path] : _paths)
        {
            LoadFont(id, path);
        }
    }

    sf::Font* SfmlFontsCollection::LoadFont(const std::string& id, const std::string& fileName)
    {
        auto path = FilePath::Path(fileName);

        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(path))
        {
            auto fontPtr = font.get();

            auto [it, isInserted] = _fonts.insert({ id, std::move(font) });
            if (isInserted)
            {
                return fontPtr;
            }
            else
            {
                Assert(false, "[SfmlFontsCollection::LoadFont] Font insertion has failed");
                return nullptr;
            }
        }

        Assert(false, "[SfmlFontsCollection::LoadFont] Font creation has failed");
        return nullptr;
    }

    sf::Font* SfmlFontsCollection::GetFont(const std::string& id)
    {
        if (auto it = _fonts.find(id); it != _fonts.end())
        {
            return it->second.get();
        }

        const auto& fontPath = GetFontPath(id);
        return LoadFont(id, fontPath);
    }

    void SfmlFontsCollection::RemoveFont(const std::string& id)
    {
        _fonts.erase(id);
    }

    const std::string& SfmlFontsCollection::GetFontPath(const std::string& id) const
    {
        if (auto it = _paths.find(id); it != _paths.end())
        {
            return it->second;
        }

        static std::string empty;
        return empty;
    }

    void SfmlFontsCollection::LoadFontsPaths(const std::string& fileName)
    {
        auto serialization = Serialization{ _systems, fileName };
        serialization.SetupElement("items");
        serialization.ForAllChildElements("item", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto path = element.GetStr("path");

            _paths.insert({ id, path });
        });
    }
}
