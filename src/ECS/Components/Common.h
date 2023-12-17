#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class Texture;
    class Shader;

    struct Transform
    {
        glm::vec3 position = glm::vec3{};
        glm::quat rotation = glm::quat{};
        glm::vec3 scale = glm::vec3{1.f};

        float GetEulerAngleZ() const;

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct RigidBody
    {
        glm::vec3 velocity = glm::vec3{};
        float inertia = 100.f;
        glm::vec3 direction = glm::vec3{};

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct BoundingBox
    {
        glm::vec3 size;
        glm::vec3 offset;

        BoundingBox(const glm::vec3& bbSize = {}, const glm::vec3& bbOffset = {});
    };

    struct PlayerInput
    {
        float speed = 0.01f;

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct Camera
    {
        glm::vec3 position = glm::vec3(0.f, 0.f, 1.f);
        glm::vec3 target = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        float fov = 45.f;
        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 projection = glm::mat4(1.f);

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct CameraTarget
    {
    };

    struct Sprite
    {
        const Texture* texture = nullptr;
        const Texture* mask = nullptr;
        Rect texRect;
        glm::vec2 size = glm::vec2(1.f);
        glm::vec2 anchor = glm::vec2(0.f);
        Shader* shader = nullptr; // pointer to shader?

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct Color
    {
        glm::vec4 rgba = glm::vec4(255.f);

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
    };

    struct SpriteFrameAnimation
    {
        std::vector<Rect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;

        static void Load(Entity entity, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, tinyxml2::XMLElement* element);
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
