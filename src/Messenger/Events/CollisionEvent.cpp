#include "CollisionEvent.h"

namespace shen
{
    CollisionEvent::CollisionEvent(Entity first, Entity second)
        : Event()
        , a(first)
        , b(second)
    { }   
}