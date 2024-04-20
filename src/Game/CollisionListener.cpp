#include "CollisionListener.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

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
        auto entityA = reinterpret_cast<entt::entity*>(bodyA->GetUserData().pointer);
        
        b2Fixture* fixtureB = contact->GetFixtureB();
        auto bodyB = fixtureB->GetBody();
        auto entityB = reinterpret_cast<entt::entity*>(bodyB->GetUserData().pointer);
    }

    void CollisionListener::EndContact(b2Contact* contact)
    {
        //
    }
}
