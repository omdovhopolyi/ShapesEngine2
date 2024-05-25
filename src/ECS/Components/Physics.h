#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/RigidBodyType.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/System/Vector2.hpp>

struct b2Body;

namespace shen
{
    class Serialization;

    struct RigidBody
    {
        RigidBodyType type = RigidBodyType::DynamicBody;
        sf::Vector2f size = sf::Vector2f(1.f, 1.f);
        bool sensor = false;

        b2Body* body = nullptr;

        static void Load(RigidBody& component, Serialization& serialization);
        static void Save(RigidBody& component, Serialization& serialization);
    };

    struct Collision
    {
        Entity other;
    };
}
