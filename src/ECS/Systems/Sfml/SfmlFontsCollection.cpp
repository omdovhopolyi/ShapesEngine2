#include "SfmlFontsCollection.h"
#include "Utils/Assert.h"
#include "tinyxml2/tinyxml2.h"

namespace shen
{
    void SfmlFontsCollection::Start()
    {
        LoadFontsPaths("../assets/configs/fonts.xml");
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
        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(fileName))
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
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile(fileName.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[SfmlFontsCollection::LoadFontsPaths] Can not read fonts path file");
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto idAttr = element->FindAttribute("id");
                const auto pathAttr = element->FindAttribute("path");

                if (!idAttr)
                {
                    Assert(!idAttr, "[SfmlFontsCollection::LoadFontsPaths] No 'id' in paths list");
                    continue;
                }

                if (!pathAttr)
                {
                    Assert(!pathAttr, "[SfmlFontsCollection::LoadFontsPaths] No 'path' in paths list");
                    continue;
                }

                const auto id = idAttr->Value();
                const auto path = pathAttr->Value();

                _paths.insert({ id, path });

                element = element->NextSiblingElement();
            }
        }
    }
}
