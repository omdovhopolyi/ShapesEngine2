#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/SpriteTypeEnum.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Transform.hpp>

struct b2Body;

namespace shen
{
    class Serialization;

    struct Transform
    {
        sf::Vector2f origin;
        sf::Vector2f position;
        sf::Vector2f scale;
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
        /*glm::quat rotation = glm::quat{};

        float GetEulerAngleZ() const;*/
    };

    struct PlayerInput
    {
        std::vector<std::string> commandTypes;

        static void Load(PlayerInput& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Camera
    {
        /*glm::vec3 position = glm::vec3(0.f, 0.f, 1.f);
        glm::vec3 target = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        float fov = 45.f;
        float nearPlane = 0.1f;
        float farPlane = 100.f;
        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 projection = glm::mat4(1.f);*/

        static void Load(Camera& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct CameraTarget
    {
    };

    struct Direction
    {
        //glm::vec3 vec = glm::vec3{};
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
