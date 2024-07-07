#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    class SfmlSpritesCollection
        : public System
    {
    public:
        void Start() override;
        void Stop() override;

        void LoadSprites(const std::string& fileName);
        sf::Sprite GetSprite(const std::string& id);
        void RemoveSprite(const std::string& id);

    private:
        std::map<std::string, sf::Sprite> _sprites;
    };
}
