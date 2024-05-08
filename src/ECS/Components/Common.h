#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/SpriteTypeEnum.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>

struct b2Body;

namespace shen
{
    class Serialization;

    struct Transform
    {
        sf::Vector2f position;
        sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
        float rotation = 0.f;

        static void Load(Transform& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Mover
    {
        float inertia = 100.f;
        /*glm::vec3 velocity = glm::vec3{};
        glm::vec3 direction = glm::vec3{};*/

        static void Load(Mover& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Rotator
    {
        float rotation = 0.f;
    };

    struct PlayerInput
    {
        std::vector<std::string> commandTypes;

        static void Load(PlayerInput& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Camera
    {
        sf::View view;
        bool needUpdate = true;

        static void Load(Camera& component, Serialization& serialization);
        static void Save(Serialization& serialization);
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
