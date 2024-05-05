#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/System/Vector2.hpp>

struct b2Body;

namespace shen
{
    class Serialization;

    struct RigidBody
    {
        int type = 0; // TODO type enum
        sf::Vector2f size = sf::Vector2f(1.f, 1.f);
        bool sensor = false;

        b2Body* body = nullptr;

        static void Load(RigidBody& component, Serialization& serialization);
        static void Save(Serialization& serialization);
    };

    struct Collision
    {
        Entity other;
    };
}
