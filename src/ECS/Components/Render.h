#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/AnimationTypeEnum.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class DataElementWrapper;

    struct Sprite
    {
        sf::Sprite sprite;
        std::string textureId;
        int sorting = 0;

        static void Load(Sprite& component, const DataElementWrapper& elementWrapper);
        static void Save(Sprite& component, DataElementWrapper& elementWrapper);
    };

    struct Color
    {
        sf::Color color;
        
        static void Load(Color& component, const DataElementWrapper& elementWrapper);
        static void Save(Color& component, DataElementWrapper& elementWrapper);
    };

    struct SpriteFrameAnimation
    {
        std::vector<sf::IntRect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;
        AnimationType animType = AnimationType::Loop;
        int totalPlayedFrames = 0;
        bool done = false;
        bool deleteOnDone = false;

        static void Load(SpriteFrameAnimation& component, const DataElementWrapper& elementWrapper);
        static void Save(SpriteFrameAnimation& component, DataElementWrapper& elementWrapper);
    };
}
