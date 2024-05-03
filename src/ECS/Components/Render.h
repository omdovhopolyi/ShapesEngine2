#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    struct Sprite
    {
        std::string textureId;
        sf::Sprite sprite;

        static void Load(Entity entity, World& world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, World& world, tinyxml2::XMLElement* element);
    };

    struct Color
    {
        sf::Color color;
        
        static void Load(Entity entity, World& world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, World& world, tinyxml2::XMLElement* element);
    };

    struct SpriteFrameAnimation
    {
        std::vector<sf::IntRect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;

        static void Load(Entity entity, World& world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, World& world, tinyxml2::XMLElement* element);
    };
}
