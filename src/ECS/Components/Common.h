#pragma once

#include "ECS/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace shen
{
    struct Transform
    {
        glm::vec3 position = glm::vec3{};
        glm::quat rotation = glm::quat{};
        glm::vec3 scale = glm::vec3{};

        Transform(const glm::vec3& pos = {});
        Transform(const glm::vec3& pos = {}, float angleZ = 0.f, const glm::vec3& scl = {});
        Transform(const glm::vec3& pos = {}, const glm::quat& rot = {}, const glm::vec3& scl = {});

        float GetEulerAngleZ() const;
    };

    struct RigidBody
    {
        glm::vec3 velocity = glm::vec3{};
        float inertia = 1.f;
        glm::vec3 direction = glm::vec3{};
    };

    struct BoundingBox
    {
        glm::vec3 size;
        glm::vec3 offset;

        BoundingBox(const glm::vec3& bbSize = {}, const glm::vec3& bbOffset = {});
    };

    struct PlayerInput
    {
        float speed = 100.f;
        PlayerInput();
    };

    struct CameraTarget
    {
    };

    struct Weapon
    {
        bool automatic = true;
        bool trigger = false;
        float delay = 1.f;
        float dt = 0.f;
    };

    struct Bullet
    {
        Entity owner;
        int damage = 10;
        float lifeTime = 3.f;
    };

    struct Health
    {
        int amount = 30;
    };

    struct SpriteAnimationDirection
    {
        int forwardSourceOffset = 0;
        int rightSourceOffset = 1;
        int backwardSourceOffset = 2;
        int leftSourceOffset = 3;
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
