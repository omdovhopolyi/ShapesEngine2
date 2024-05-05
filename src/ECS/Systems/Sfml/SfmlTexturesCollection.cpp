#include "SfmlTexturesCollection.h"
#include <SFML/Graphics/Texture.hpp>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    void SfmlTexturesCollection::Start()
    {
        LoadTexturesPaths("../assets/configs/textures.xml");
    }

    void SfmlTexturesCollection::Stop()
    {
        _textures.clear();
    }

    void SfmlTexturesCollection::LoadTextures()
    {
        for (const auto& [id, path] : _paths)
        {
            LoadTexture(id, path);
        }
    }

    sf::Texture* SfmlTexturesCollection::LoadTexture(const std::string& id, const std::string& fileName)
    {
        auto texture = std::make_unique<sf::Texture>();

        if (texture->loadFromFile("image.png"))
        {
            auto texturePtr = texture.get();

            auto [it, isInserted] = _textures.insert({ id, std::move(texture) });
            if (isInserted)
            {
                return texturePtr;
            }
            else
            {
                // TODO assert log
                return nullptr;
            }
        }

        // TODO assert log
        return nullptr;
    }

    sf::Texture* SfmlTexturesCollection::GetTexture(const std::string& textureId)
    {
        if (auto it = _textures.find(textureId); it != _textures.end())
        {
            return it->second.get();
        }
        
        return LoadTexture(textureId, "");    
    }

    void SfmlTexturesCollection::RemoveTexture(const std::string& id)
    {
        _textures.erase(id);
    }

    const std::string& SfmlTexturesCollection::GetTexturePath(const std::string& id) const
    {
        if (auto it = _paths.find(id); it != _paths.end())
        {
            return it->second;
        }

        static std::string empty;
        return empty;
    }

    void SfmlTexturesCollection::LoadTexturesPaths(const std::string& fileName)
    {
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile(fileName.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            // TODO assert
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto idAttr = element->FindAttribute("id");
                const auto pathAttr = element->FindAttribute("path");

                if (!idAttr || !pathAttr)
                {
                    // TODO assert
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