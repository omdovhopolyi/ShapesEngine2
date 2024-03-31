#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/SpriteTypeEnum.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <tinyxml2/tinyxml2.h>

struct b2Body;

namespace shen
{
    struct Transform
    {
        glm::vec3 position = glm::vec3{};
        glm::quat rotation = glm::quat{};
        glm::vec3 scale = glm::vec3{1.f};

        float GetEulerAngleZ() const;

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Mover
    {
        glm::vec3 velocity = glm::vec3{};
        float inertia = 100.f;
        glm::vec3 direction = glm::vec3{};

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Rotator
    {
        glm::quat rotation = glm::quat{};

        float GetEulerAngleZ() const;
    };

    struct PlayerInput
    {
        std::vector<std::string> commandTypes;

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Camera
    {
        glm::vec3 position = glm::vec3(0.f, 0.f, 1.f);
        glm::vec3 target = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        float fov = 45.f;
        float nearPlane = 0.1f;
        float farPlane = 100.f;
        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 projection = glm::mat4(1.f);

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct CameraTarget
    {
    };

    struct Direction
    {
        glm::vec3 vec = glm::vec3{};
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
