#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    struct SfmlSpriteData
    {
        sf::Sprite sprite;
        std::string textureId;
    };

    class SfmlSpritesCollection
        : public System
    {
        SYSTEMS_FACTORY(SfmlSpritesCollection)

    public:
        void Start() override;
        void Stop() override;

        void LoadSprites(const std::string& fileName);
        sf::Sprite GetSprite(const std::string& id) const;
        const SfmlSpriteData& GetSpriteData(const std::string& id) const;
        const std::string GetSpritesTexId(const std::string& id) const;
        void RemoveSprite(const std::string& id);

    private:
        std::map<std::string, SfmlSpriteData> _sprites;
    };
}
