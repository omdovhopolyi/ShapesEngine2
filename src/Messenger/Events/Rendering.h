#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Utils/Types.h"

namespace shen
{
    struct UpdateTexRect
        : Event
    {
        Entity entity;
        Rect texRect;

        UpdateTexRect(Entity ent, const Rect& rect)
            : Event()
            , entity(ent)
            , texRect(rect)
        {}
    };
}