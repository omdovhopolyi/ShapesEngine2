#pragma once

#include "Event.h"
#include "ECS/Entity.h"

namespace shen
{
    struct CollisionEvent
        : Event
    {
        Entity a;
        Entity b;

        CollisionEvent(Entity a, Entity b);
    };
}