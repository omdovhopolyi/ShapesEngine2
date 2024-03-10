#include "PhysicsBox2DSystem.h"
#include "Game/Time.h"
#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void PhysicsBox2DSystem::Start()
    {
        _world = std::make_unique<b2World>(b2Vec2(0.0f, -9.8f));
        if (!_world)
        {
            // Assert
            return;
        }

        _collisionListener = std::make_unique<CollisionListener>();
        _world->SetContactListener(_collisionListener.get());

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<Sprite, Box2DBody, Transform>(
            [&](const auto entity, Sprite& sprite, Box2DBody& body, Transform& transform)
            {
                const auto pos = transform.position;

                // TODO define body size config
                const auto size = glm::vec3(sprite.size, 0.f) * transform.scale;
                const auto anchorOffset = size * glm::vec3(sprite.anchor, 0.f);

                b2BodyDef bodyDef;
                bodyDef.type = static_cast<b2BodyType>(body.type);
                bodyDef.position.Set(pos.x/* - anchorOffset.x*/, pos.y/* - anchorOffset.y*/);
                bodyDef.angle = glm::radians(transform.GetEulerAngleZ());
                auto dynamicBody = _world->CreateBody(&bodyDef);

                body.body = dynamicBody;

                b2PolygonShape dynamicBox;
                dynamicBox.SetAsBox(size.x / 2.f, size.y / 2.f);
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &dynamicBox;
                fixtureDef.density = 1.0f;
                dynamicBody->CreateFixture(&fixtureDef);
            });
    }

    void PhysicsBox2DSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();

        //float timeStep = 1.0f / 60.0f;  // 60Hz
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world->Step(dt, velocityIterations, positionIterations);

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<Box2DBody, Sprite, Transform>(
            [&](const auto entity, Box2DBody& bodyHolder, Sprite& sprite, Transform& transform)
            {
                auto position = bodyHolder.body->GetPosition();
                const auto angle = bodyHolder.body->GetAngle();

                glm::vec3 size = glm::vec3(sprite.size, 0.f) * transform.scale;
                position.x += size.x * (sprite.anchor.x - 0.5f);
                position.y += size.y * (sprite.anchor.y - 0.5f);
                
                static glm::vec3 up{ 0.f, 0.f, 1.f };
                transform.position = glm::vec3(position.x, position.y, 0.f);
                transform.rotation = glm::angleAxis(angle, up);
            });
    }

    void PhysicsBox2DSystem::Stop()
    {

    }
}
