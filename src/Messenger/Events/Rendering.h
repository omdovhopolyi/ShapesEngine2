#pragma once

#include "Event.h"
#include "ECS/Entity.h"
#include "Utils/Types.h"
#include <SFML/Graphics/Rect.hpp>

namespace shen
{
    struct UpdateTexRect
        : Event
    {
        Entity entity;
        sf::IntRect texRect;

        UpdateTexRect(Entity ent, const sf::IntRect& rect)
            : Event()
            , entity(ent)
            , texRect(rect)
        {}
    };
}