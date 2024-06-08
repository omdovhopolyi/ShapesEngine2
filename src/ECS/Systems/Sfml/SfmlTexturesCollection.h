#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    class SfmlTexturesCollection
        : public System
    {
    public:
        void Start() override;
        void Stop() override;

        void LoadTextures();
        sf::Texture* LoadTexture(const std::string& id, const std::string& fileName);
        sf::Texture* GetTexture(const std::string& textureId);
        void RemoveTexture(const std::string& id);
        const std::string& GetTexturePath(const std::string& id) const;

    public:
        void LoadTexturesPaths(const std::string& fileName);

    private:
        std::map<std::string, std::unique_ptr<sf::Texture>> _textures;
        std::map<std::string, std::string> _paths;

        bool _flipTexOnLoad = true;
    };
}
