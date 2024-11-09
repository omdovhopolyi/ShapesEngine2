#include "CollisionListener.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Entity.h"

namespace shen
{
    CollisionListener::CollisionListener(World* world)
        : b2ContactListener()
        , _world(world)
    {}

    void CollisionListener::BeginContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        auto bodyA = fixtureA->GetBody();    
        auto entityA = Entity{ static_cast<std::uint32_t>(bodyA->GetUserData().pointer) };
        
        b2Fixture* fixtureB = contact->GetFixtureB();
        auto bodyB = fixtureB->GetBody();
        auto entityB = Entity{ static_cast<std::uint32_t>(bodyB->GetUserData().pointer) };

        auto collisionA = _world->AddComponent<Collision>(entityA);
        collisionA->other = entityB;

        auto collisionB = _world->AddComponent<Collision>(entityB);
        collisionB->other = entityA;
    }

    void CollisionListener::EndContact(b2Contact* contact)
    {
        //
    }
}
