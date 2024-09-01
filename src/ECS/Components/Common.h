#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <set>

struct b2Body;

namespace shen
{
    class Serialization;

    struct Transform
    {
        sf::Vector2f position;
        sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
        float rotation = 0.f;

        static void Load(Transform& component, const Serialization& serialization);
        static void Save(Transform& component, Serialization& serialization);
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
    {
        std::set<std::string> commandTypes;

        static void Load(PlayerInput& component, const Serialization& serialization);
        static void Save(PlayerInput& component, Serialization& serialization);
    };

    struct Camera
    {
        sf::View view;
        std::string type;
        float scale = 1.f;
        bool needUpdate = true;

        static void Load(Camera& component, const Serialization& serialization);
        static void Save(Camera& component, Serialization& serialization);
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
