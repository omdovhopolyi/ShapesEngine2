#include "CollisionListener.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Game/ManagersProvider.h"

namespace shen
{
    void CollisionListener::BeginContact(b2Contact* contact)
    {
        auto world = ManagersProvider::Instance().GetWorld();
        
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
