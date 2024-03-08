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

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<Sprite, Transform>(
            [&](const auto entity, Sprite& sprite, Transform& transform)
            {
                const auto pos = transform.position;

                glm::vec3 size = glm::vec3(sprite.size, 1.f) * transform.scale;

                b2BodyDef bodyDef;
                bodyDef.type = b2_dynamicBody;
                bodyDef.position.Set(pos.x, pos.y);
                auto dynamicBody = _world->CreateBody(&bodyDef);

                auto bodyHolder = gameWorld->AddComponent<Box2DBody>(entity);
                bodyHolder->body = dynamicBody;

                b2PolygonShape dynamicBox;
                dynamicBox.SetAsBox(size.x, size.y);
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &dynamicBox;
                fixtureDef.density = 1.0f;  // Density affects mass
                dynamicBody->CreateFixture(&fixtureDef);
            });
    }

    void PhysicsBox2DSystem::Update()
    {
        const auto dt = ManagersProvider::Instance().GetTime()->Dt();

        //float32 timeStep = 1.0f / 60.0f;  // 60Hz
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        _world->Step(dt, velocityIterations, positionIterations);

        auto gameWorld = ManagersProvider::Instance().GetWorld();

        gameWorld->Each<Box2DBody, Transform>(
            [&](const auto entity, Box2DBody& bodyHolder, Transform& transform)
            {
                const auto position = bodyHolder.body->GetPosition();
                const auto angle = bodyHolder.body->GetAngle();

                static glm::vec3 up{ 0.f, 0.f, 1.f };
                transform.position = glm::vec3(position.x, position.y, 0.f);
                transform.rotation = glm::angleAxis(glm::radians(angle), up);
            });

        //for (b2Body* body = world.GetBodyList(); body; body = body->GetNext()) {
        //    // Get position and rotation
        //    b2Vec2 position = body->GetPosition();
        //    float32 angle = body->GetAngle();

        //    // Render the object using position and angle
        //    renderObject(position.x, position.y, angle);
        //}
    }

    void PhysicsBox2DSystem::Stop()
    {

    }
}
