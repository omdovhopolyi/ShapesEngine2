#include "SfmlTexturesCollection.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/Serialization.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/../extlibs/headers/stb_image/stb_image.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlTexturesCollection)

    void SfmlTexturesCollection::Start()
    {
        stbi_set_flip_vertically_on_load(_flipTexOnLoad);
        LoadTexturesPaths(FilePath::Path("assets/configs/textures.xml"));
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
        auto path = FilePath::Path(fileName);

        auto texture = std::make_unique<sf::Texture>();

        if (texture->loadFromFile(path))
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
