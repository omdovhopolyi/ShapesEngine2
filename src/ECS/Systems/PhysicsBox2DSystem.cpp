#include "PhysicsBox2DSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Utils/Math.h"
#include "Utils/Assert.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(PhysicsBox2DSystem)

    static float PxlPerMeter = 32.f;

    void PhysicsBox2DSystem::Start()
    {
        _world = std::make_unique<b2World>(b2Vec2(0.f, 0.f/*-9.8f*/));
        if (!_world)
        {
            Assert(!_world, "[PhysicsBox2DSystem::Start] Can not create b2World");
            return;
        }

        _collisionListener = std::make_unique<CollisionListener>(&_systems->GetWorld());
        _world->SetContactListener(_collisionListener.get());

        auto& gameWorld = _systems->GetWorld();

        gameWorld.Each<RigidBody, Transform>(
            [&](const auto& entity, RigidBody& rb, Transform& transform)
        {
            b2BodyDef bodyDef;
            bodyDef.type = static_cast<b2BodyType>(rb.type);
            bodyDef.position.Set(transform.position.x / PxlPerMeter, transform.position.y / PxlPerMeter);
            bodyDef.angle = Radians(transform.rotation);

            auto dynamicBody = _world->CreateBody(&bodyDef);
            dynamicBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(&entity);

            rb.body = dynamicBody;

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(rb.size.x / 2.f, rb.size.y / 2.f);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            fixtureDef.density = 1.f;
            fixtureDef.isSensor = rb.sensor;

            dynamicBody->CreateFixture(&fixtureDef);
        });
    }

    void PhysicsBox2DSystem::Update()
    {
        auto& gameWorld = _systems->GetWorld();
        auto time = _systems->GetSystem<TimeSystem>();

        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world->Step(time->Dt(), velocityIterations, positionIterations);

        gameWorld.Each<RigidBody, Transform>(
            [&](const auto entity, RigidBody& rb, Transform& transform)
        {
            auto position = rb.body->GetPosition();
            const auto angle = rb.body->GetAngle();

            transform.position = sf::Vector2f(position.x * PxlPerMeter, position.y * PxlPerMeter);
            transform.rotation = Degrees(angle);
        });
    }

    void PhysicsBox2DSystem::Stop()
    {

    }
}
