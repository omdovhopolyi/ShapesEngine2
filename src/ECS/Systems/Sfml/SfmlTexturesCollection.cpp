#include "SfmlTexturesCollection.h"
#include "Utils/Assert.h"
#include <SFML/Graphics/Texture.hpp>
#include <tinyxml2/tinyxml2.h>


#include <SFML/../extlibs/headers/stb_image/stb_image.h>

namespace shen
{
    void SfmlTexturesCollection::Start()
    {
        stbi_set_flip_vertically_on_load(_flipTexOnLoad);
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

        if (texture->loadFromFile(fileName))
        {
            auto texturePtr = texture.get();

            auto [it, isInserted] = _textures.insert({ id, std::move(texture) });
            if (isInserted)
            {
                return texturePtr;
            }
            else
            {
                Assert(false, "[SfmlTexturesCollection::LoadTexture] Texture insertion has failed");
                // TODO assert log
                return nullptr;
            }
        }

        Assert(false, "[SfmlTexturesCollection::LoadTexture] Texture creation has failed");
        return nullptr;
    }

    sf::Texture* SfmlTexturesCollection::GetTexture(const std::string& textureId)
    {
        if (auto it = _textures.find(textureId); it != _textures.end())
        {
            return it->second.get();
        }
        
        const auto& texturePath = GetTexturePath(textureId);

        return LoadTexture(textureId, texturePath);    
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
            Assert(error != tinyxml2::XML_SUCCESS, "[SfmlTexturesCollection::LoadTexturesPaths] Can not read textures path file");
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
                    Assert(!idAttr, "[SfmlTexturesCollection::LoadTexturesPaths] No 'id' in paths list");
                    continue;
                }

                if (!pathAttr)
                {
                    Assert(!pathAttr, "[SfmlTexturesCollection::LoadTexturesPaths] No 'path' in paths list");
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
