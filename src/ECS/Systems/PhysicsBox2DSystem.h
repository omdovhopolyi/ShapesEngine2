#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "Physics/CollisionListener.h"
#include "ECS/Entity.h"
#include "Messenger/SubscriptionsContainer.h"
#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace shen
{
    class PhysicsBox2DSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(PhysicsBox2DSystem)

    public:
        void Start() override;
        void Update() override;
        void Stop() override;

        void SetupDefaultCollisionListener();
        void SetCollisionListener(std::unique_ptr<CollisionListener>& listener);

        bool InitWorld();
        void InitRigidBodies();

        void SetupRigidBody(Entity entity);

		void SetLinearVelocity(Entity entity, const sf::Vector2f& velocity);
		void SetAngularVelocity(Entity entity, float omega);
		void ApplyForce(Entity entity, const sf::Vector2f& force, const sf::Vector2f& point, bool wake = true);
		void ApplyForceToCenter(Entity entity, const sf::Vector2f& force, bool wake = true);
		void ApplyTorque(Entity entity, float torque, bool wake = true);
		void ApplyLinearImpulse(Entity entity, const sf::Vector2f& impulse, const sf::Vector2f& point, bool wake = true);
		void ApplyLinearImpulseToCenter(Entity entity, const sf::Vector2f& impulse, bool wake = true);
		void ApplyAngularImpulse(Entity entity, float impulse, bool wake = true);

        void DestroyBody(Entity entity);

        void Pause(bool pause);
        bool IsPaused() const;

        void ResetAccumulatedTime();

        static sf::Vector2f Box2dPosToWorld(const b2Vec2& box2dPos);
        static b2Vec2 WorldToBox2dPos(const sf::Vector2f& worldPos);

    private:
        void InitSubscriptions();
        void UpdatePhysics();

        void OnMapLoaded(const std::string& mapId);

        b2Body* GetB2Body(Entity entity);

    private:
        std::unique_ptr<b2World> _world;
        std::unique_ptr<CollisionListener> _collisionListener;

        int32 _velocityIterations = 6;
        int32 _positionIterations = 2;

        float _accumulatedDt = 0.f;
        bool _pause = true;

        SubcriptionsContainer _subscriptions;
    };
}
