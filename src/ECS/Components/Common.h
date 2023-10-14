#pragma once

#include "ECS/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace shen
{
    class Texture;

    struct Transform
    {
        glm::vec3 position = glm::vec3{};
        glm::quat rotation = glm::quat{};
        glm::vec3 scale = glm::vec3{};

        /*Transform() = default;
        Transform(const glm::vec3& pos = {});
        Transform(const glm::vec3& pos = {}, float angleZ = 0.f, const glm::vec3& scl = {});
        Transform(const glm::vec3& pos = {}, const glm::quat& rot = {}, const glm::vec3& scl = {});*/

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

    struct CameraComp
    {
        glm::vec3 position = glm::vec3(0.f, 0.f, 1.f);
        glm::vec3 target = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        float fov = 45.f;
        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 projection = glm::mat4(1.f);
    };

    struct CameraTarget
    {
    };

    struct Sprite
    {
        const Texture* texture = nullptr;
        glm::vec2 texOrigin;
        glm::vec2 texSize;
        glm::vec2 size;
        glm::vec2 anchor = glm::vec2(0.f);
        std::string shader;
    };

    struct Buffers
    {
        unsigned int VBO = 0;
        unsigned int UV = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
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
