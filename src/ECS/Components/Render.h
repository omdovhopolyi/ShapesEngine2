#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include "Enums/SpriteTypeEnum.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class Texture;
    class Shader;

    struct Sprite
    {
        const Texture* texture = nullptr;
        const Texture* mask = nullptr;
        Rect texRect;
        glm::vec2 size = glm::vec2(1.f);
        glm::vec2 anchor = glm::vec2(0.f);
        Shader* shader = nullptr;
        SpriteType spriteType = SpriteType::OneType;

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Color
    {
        glm::vec4 rgba = glm::vec4(255.f);

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct SpriteFrameAnimation
    {
        std::vector<Rect> frames;
        float frameTime = 1.f;
        float dt = 0.f;
        int curFrame = 0;

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Buffers
    {
        unsigned int VBO = 0;
        unsigned int UV = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
    };
}
