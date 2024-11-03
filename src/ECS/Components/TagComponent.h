#pragma once

#include "ECS/Entity.h"
#include "Utils/Types.h"
#include "Enums/EnumUtils.h"
#include <tinyxml2/tinyxml2.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <set>

struct b2Body;

namespace shen
{
    // entty may has problems working with empty structs
    // this is one of the problem resolution
    struct TagBaseComponent
    {
        const bool dummy = true;
    };
}
