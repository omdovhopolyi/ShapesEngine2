#include "PhysicsBox2DSystem.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"

namespace shen
{
    void PhysicsBox2DSystem::Start()
    {
        _world = std::make_unique<b2World>(b2Vec2(0.f, 0.f/*-9.8f*/));
        if (!_world)
        {
            // Assert
            return;
        }

        _collisionListener = std::make_unique<CollisionListener>();
        _world->SetContactListener(_collisionListener.get());

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<RigidBody, Transform>(
            [&](const auto& entity, RigidBody& rb, Transform& transform)
            {
                const auto size = glm::vec3(rb.size, 0.f) * transform.scale;
                
                b2BodyDef bodyDef;
                bodyDef.type = static_cast<b2BodyType>(rb.type);
                bodyDef.position.Set(transform.position.x, transform.position.y);
                bodyDef.angle = glm::radians(transform.GetEulerAngleZ());

                auto dynamicBody = _world->CreateBody(&bodyDef);
                dynamicBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(&entity);

                rb.body = dynamicBody;

                b2PolygonShape dynamicBox;
                dynamicBox.SetAsBox(size.x / 2.f, size.y / 2.f);
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &dynamicBox;
                fixtureDef.density = 1.f;
                fixtureDef.isSensor = rb.sensor;

                dynamicBody->CreateFixture(&fixtureDef);
            });
    }

    void PhysicsBox2DSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();

        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world->Step(dt, velocityIterations, positionIterations);

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<RigidBody, Transform>(
            [&](const auto entity, RigidBody& rb, Transform& transform)
            {
                auto position = rb.body->GetPosition();
                const auto angle = rb.body->GetAngle();

                static glm::vec3 up{ 0.f, 0.f, 1.f };
                transform.position = glm::vec3(position.x, position.y, 0.f);
                transform.rotation = glm::angleAxis(angle, up);
            });
    }

    void PhysicsBox2DSystem::Stop()
    {

    }
}
