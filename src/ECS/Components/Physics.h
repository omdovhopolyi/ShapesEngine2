#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/RigidBodyType.h"
#include "Serialization/Serializable.h"
#include <SFML/System/Vector2.hpp>

struct b2Body;

namespace shen
{
    class DataElementWrapper;

    struct RigidBody
        : public Serializable
    {
        SERIALIZABLE_COMP(RigidBody)

        void RegisterProperties() override;
        void AfterLoad() override;

        RigidBodyType GetType() const;
        void SetType(RigidBodyType type);
        void SetType(const std::string& typeStr);

    public:
        sf::Vector2f size = sf::Vector2f(1.f, 1.f);
        bool sensor = false;
        b2Body* body = nullptr;

    private:
        std::string _typeStr;
        RigidBodyType _type = RigidBodyType::DynamicBody;
    };

    struct Collision
    {
        Entity other;
    };
}
