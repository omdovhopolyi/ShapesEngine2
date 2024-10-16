#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class Serialization;

    struct Sprite
    {
        sf::Sprite sprite;
        std::string textureId;

        static void Load(Sprite& component, const Serialization& serialization);
        static void Save(Sprite& component, Serialization& serialization);
    };

    struct Color
    {
        sf::Color color;
        
        static void Load(Color& component, const Serialization& serialization);
        static void Save(Color& component, Serialization& serialization);
    };

    struct SpriteFrameAnimation
    {
        std::vector<sf::IntRect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;

        static void Load(SpriteFrameAnimation& component, const Serialization& serialization);
        static void Save(SpriteFrameAnimation& component, Serialization& serialization);
    };
}
