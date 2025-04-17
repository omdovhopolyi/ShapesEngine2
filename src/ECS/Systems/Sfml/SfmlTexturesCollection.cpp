#include "SfmlTexturesCollection.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
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
        for (const auto& [id, data] : _texturesData)
        {
            LoadTexture(id, &data);
        }
    }

    sf::Texture* SfmlTexturesCollection::LoadTexture(const std::string& id, const TextureData* data)
    {
        auto path = FilePath::Path(data->path);

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
        
        const auto textureData = GetTextureData(textureId);

        return LoadTexture(textureId, textureData);    
    }

    void SfmlTexturesCollection::RemoveTexture(const std::string& id)
    {
        _textures.erase(id);
    }

    const TextureData* SfmlTexturesCollection::GetTextureData(const std::string& id) const
    {
        if (auto it = _texturesData.find(id); it != _texturesData.end())
        {
            return &it->second;
        }

        return nullptr;
    }

    void SfmlTexturesCollection::LoadTexturesPaths(const std::string& fileName)
    {
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(fileName);
        elementWrapper.ForAllChildren("item", [&](const DataElementWrapper& element)
        {
            const auto id = element.GetStr("id");
            const auto path = element.GetStr("path");
            const auto needPreload = element.GetBool("preload");
            const auto smooth = element.GetBool("smooth", true);

            auto textureData = TextureData{ path, smooth };
            _texturesData.insert({ id, textureData });
            
            if (needPreload)
            {
                if (const auto texture = GetTexture(id))
                {
                    texture->setSmooth(smooth);
                }
            }
        });
    }
}
