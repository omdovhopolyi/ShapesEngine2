#pragma once

#include <box2d/box2d.h>

namespace shen
{
    class CollisionListener
        : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact* contact) override;
    };
}
