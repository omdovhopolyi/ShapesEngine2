#pragma once

#include <box2d/box2d.h>

namespace shen
{
    class World;

    class CollisionListener
        : public b2ContactListener
    {
    public:
        CollisionListener(World* world);

        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;

    private:
        World* _world = nullptr;
    };
}
