#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Serialization/Serializable.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <set>

struct b2Body;

namespace shen
{
    class DataElementWrapper;

    struct Transform
        : public Serializable
    {
        SERIALIZABLE_COMP(Transform)

        sf::Vector2f position;
        sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
        float rotation = 0.f;

        void RegisterProperties() override;
    };

    struct Mover
    {
        sf::Vector2f velocity;
        sf::Vector2f direction;
        sf::Vector2f position;
    };

    struct Rotator
    {
        float rotation = 0.f;
    };

    struct PlayerInput
        : public Serializable
    {
        SERIALIZABLE_COMP(PlayerInput)

        std::set<std::string> commandTypes;

        void RegisterProperties() override;
    };

    struct Camera
        : public Serializable
    {
        SERIALIZABLE_COMP(Camera)

        sf::View view;
        std::string type;
        float scale = 1.f;
        bool needUpdate = true;

        void RegisterProperties() override;
    };

    struct CameraTarget
    {
    };

    struct Direction
    {
        sf::Vector2f dir;
    };

    struct Tag
    {
        std::string tag;
    };

    struct Group
    {
        std::string group;
    };

    struct Destroy {};
}
