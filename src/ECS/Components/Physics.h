#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include <tinyxml2/tinyxml2.h>

struct b2Body;

namespace shen
{
    class EcsWorld;

    struct RigidBody
    {
        int type = 0; // TODO type enum
        glm::vec2 size = glm::vec2(1.f);
        bool sensor = false;

        b2Body* body = nullptr;

        static void Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element);
        static void Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element);
    };

    struct Collision
    {
        Entity other;
    };
}
