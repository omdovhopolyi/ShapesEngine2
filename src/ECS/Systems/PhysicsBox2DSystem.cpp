#include "PhysicsBox2DSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Utils/Math.h"
#include "Utils/Assert.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(PhysicsBox2DSystem)

    // TODO config
    static float PxlPerMeter = 32.f;
    static float TimeStep = 1.f / 90.f;

    void PhysicsBox2DSystem::Start()
    {
        InitSubscriptions();
        InitWorld();
        SetupDefaultCollisionListener();
        InitRigidBodies();
    }

    void PhysicsBox2DSystem::Update()
    {
        UpdatePhysics();
    }

    void PhysicsBox2DSystem::Stop()
    {
        _collisionListener.reset();
        _world.reset();
    }

    void PhysicsBox2DSystem::SetupDefaultCollisionListener()
    {
        _collisionListener = std::make_unique<CollisionListener>(&_systems->GetWorld());
        _world->SetContactListener(_collisionListener.get());
    }

    void PhysicsBox2DSystem::SetCollisionListener(std::unique_ptr<CollisionListener>& listener)
    {
        _collisionListener = std::move(listener);
        _world->SetContactListener(_collisionListener.get());
    }

    bool PhysicsBox2DSystem::InitWorld()
    {
        _world = std::make_unique<b2World>(b2Vec2(0.f, 0.f/*-9.8f*/));
        if (!_world)
        {
            Assert(!_world, "[PhysicsBox2DSystem::Start] Can not create b2World");
            return false;
        }

        return true;
    }

    void PhysicsBox2DSystem::InitRigidBodies()
    {
        auto& gameWorld = _systems->GetWorld();

        gameWorld.Each<RigidBody, Transform>(
            [&](const Entity& entity, RigidBody& rb, Transform& transform)
        {
            if (!rb.body)
            {
                b2BodyDef bodyDef;
                bodyDef.type = static_cast<b2BodyType>(rb.type);
                bodyDef.position.Set(transform.position.x / PxlPerMeter, transform.position.y / PxlPerMeter);
                bodyDef.angle = Radians(transform.rotation);

                auto dynamicBody = _world->CreateBody(&bodyDef);
                dynamicBody->GetUserData().pointer = static_cast<uintptr_t>(entity.GetId());

                rb.body = dynamicBody;

                b2PolygonShape dynamicBox;
                dynamicBox.SetAsBox(rb.size.x / 2.f, rb.size.y / 2.f);

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &dynamicBox;
                fixtureDef.density = 1.f;
                fixtureDef.isSensor = rb.sensor;

                dynamicBody->CreateFixture(&fixtureDef);
            }
        });
    }

    void PhysicsBox2DSystem::SetupRigidBody(Entity entity)
    {
        auto& world = _systems->GetWorld();
        auto rb = world.GetComponent<RigidBody>(entity);
        auto transform = world.GetComponent<Transform>(entity);

        if (rb && transform)
        {
            b2BodyDef bodyDef;
            bodyDef.type = static_cast<b2BodyType>(rb->type);
            bodyDef.position.Set(transform->position.x / PxlPerMeter, transform->position.y / PxlPerMeter);
            bodyDef.angle = Radians(transform->rotation);

            auto dynamicBody = _world->CreateBody(&bodyDef);
            dynamicBody->GetUserData().pointer = static_cast<uintptr_t>(entity.GetId());

            rb->body = dynamicBody;

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(rb->size.x / 2.f, rb->size.y / 2.f);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            fixtureDef.density = 1.f;
            fixtureDef.isSensor = rb->sensor;

            dynamicBody->CreateFixture(&fixtureDef);
        }
    }

    void PhysicsBox2DSystem::SetLinearVelocity(Entity entity, const sf::Vector2f& velocity)
    {
        if (auto body = GetB2Body(entity))
        {
            body->SetLinearVelocity({ velocity.x, velocity.y });
        }
    }

    void PhysicsBox2DSystem::SetAngularVelocity(Entity entity, float omega)
    {
        if (auto body = GetB2Body(entity))
        {
            body->SetAngularVelocity(omega);
        }
    }

    void PhysicsBox2DSystem::ApplyForce(Entity entity, const sf::Vector2f& force, const sf::Vector2f& point, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyForce({ force.x, force.y }, { point.x, point.y }, wake);
        }
    }

    void PhysicsBox2DSystem::ApplyForceToCenter(Entity entity, const sf::Vector2f& force, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyForceToCenter({ force.x, force.y }, wake);
        }
    }

    void PhysicsBox2DSystem::ApplyTorque(Entity entity, float torque, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyTorque(torque, wake);
        }
    }

    void PhysicsBox2DSystem::ApplyLinearImpulse(Entity entity, const sf::Vector2f& impulse, const sf::Vector2f& point, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyLinearImpulse({ impulse.x, impulse.y }, { point.x, point.y }, wake);
        }
    }

    void PhysicsBox2DSystem::ApplyLinearImpulseToCenter(Entity entity, const sf::Vector2f& impulse, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyLinearImpulseToCenter({ impulse.x, impulse.y }, wake);
        }
    }

    void PhysicsBox2DSystem::ApplyAngularImpulse(Entity entity, float impulse, bool wake)
    {
        if (auto body = GetB2Body(entity))
        {
            body->ApplyAngularImpulse(impulse, wake);
        }
    }

    void PhysicsBox2DSystem::DestroyBody(Entity entity)
    {
        if (auto body = GetB2Body(entity))
        {
            _world->DestroyBody(body);
        }
    }

    void PhysicsBox2DSystem::Pause(bool pause)
    {
        _pause = pause;
    }

    bool PhysicsBox2DSystem::IsPaused() const
    {
        return _pause;
    }

    void PhysicsBox2DSystem::ResetAccumulatedTime()
    {
        _accumulatedDt = 0.f;
    }

    sf::Vector2f PhysicsBox2DSystem::Box2dPosToWorld(const b2Vec2& box2dPos)
    {
        return sf::Vector2f{ box2dPos.x * PxlPerMeter, box2dPos.y * PxlPerMeter };
    }

    b2Vec2 PhysicsBox2DSystem::WorldToBox2dPos(const sf::Vector2f& worldPos)
    {
        return b2Vec2{ worldPos.x / PxlPerMeter, worldPos.y / PxlPerMeter };
    }

    void PhysicsBox2DSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<MapLoadedEvent>([&](const MapLoadedEvent& event)
        {
            OnMapLoaded(event.mapId);
        });
    }

    void PhysicsBox2DSystem::UpdatePhysics()
    {
        if (IsPaused())
        {
            return;
        }

        auto& gameWorld = _systems->GetWorld();
        auto dt = _systems->GetSystem<TimeSystem>()->GameDt();
        _accumulatedDt += dt;

        while (_accumulatedDt >= TimeStep)
        {
            _world->Step(TimeStep, _velocityIterations, _positionIterations);
            _accumulatedDt -= TimeStep;
        }

        gameWorld.Each<RigidBody, Transform>(
            [&](const auto entity, RigidBody& rb, Transform& transform)
        {
            auto position = rb.body->GetPosition();
            const auto angle = rb.body->GetAngle();

            transform.position = sf::Vector2f(position.x * PxlPerMeter, position.y * PxlPerMeter);
            transform.rotation = Degrees(angle);
        });
    }

    void PhysicsBox2DSystem::OnMapLoaded(const std::string& mapId)
    {
        InitRigidBodies();
    }

    b2Body* PhysicsBox2DSystem::GetB2Body(Entity entity)
    {
        auto& world = _systems->GetWorld();
        if (auto rb = world.GetComponent<RigidBody>(entity))
        {
            return rb->body;
        }

        return nullptr;
    }
}
