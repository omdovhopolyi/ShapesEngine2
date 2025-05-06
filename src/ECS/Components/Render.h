#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/AnimationTypeEnum.h"
#include "Serialization/Serializable.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace shen
{
    class DataElementWrapper;

    struct Sprite
        : public Serializable
    {
        SERIALIZABLE_COMP(Sprite)

        sf::Sprite sprite;
        sf::IntRect rect;
        sf::Vector2f anchor;
        std::string textureId;
        int sorting = 0;
        bool autoRect = true;
        bool autoAnchor = true;

        void RegisterProperties() override;
        void AfterLoad() override;
    };

    struct Color
        : public Serializable
    {
        SERIALIZABLE_COMP(Color)

        sf::Color color;

        void RegisterProperties() override;
    };

    struct SpriteFrameAnimation
        : public Serializable
    {
        SERIALIZABLE_COMP(SpriteFrameAnimation)

        std::vector<sf::IntRect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;
        AnimationType animType = AnimationType::Loop;
        std::string animTypeStr;
        int totalPlayedFrames = 0;
        bool done = false;
        bool deleteOnDone = false;

        void RegisterProperties() override;
        void AfterLoad() override;
    };
}
