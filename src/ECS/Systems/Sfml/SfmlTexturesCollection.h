#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    struct TextureData
    {
        std::string path;
        bool smooth = true;
    };

    class SfmlTexturesCollection
        : public System
    {
        SYSTEMS_FACTORY(SfmlTexturesCollection)

    public:
        void Start() override;
        void Stop() override;

        void LoadTextures();
        sf::Texture* LoadTexture(const std::string& id, const TextureData* data);
        sf::Texture* GetTexture(const std::string& textureId);
        void RemoveTexture(const std::string& id);
        const TextureData* GetTextureData(const std::string& id) const;

    public:
        void LoadTexturesPaths(const std::string& fileName);

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _textures;
        std::unordered_map<std::string, TextureData> _texturesData;

        bool _flipTexOnLoad = false;
    };
}
