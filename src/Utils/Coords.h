#pragma once

#include "ECS/Entity.h"
#include <glm/glm.hpp>

namespace shen
{
    glm::vec3 ScreenToWorld(const glm::vec2& screenPos);
    glm::vec2 ObjectWorldPosition2D(Entity entity);
}
