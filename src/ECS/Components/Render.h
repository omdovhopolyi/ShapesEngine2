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

        static void Load(Sprite& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Color
    {
        sf::Color color;
        
        static void Load(Color& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct SpriteFrameAnimation
    {
        std::vector<sf::IntRect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;

        static void Load(SpriteFrameAnimation& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };
}
