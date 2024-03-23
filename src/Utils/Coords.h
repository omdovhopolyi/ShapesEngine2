#pragma once

#include "ECS/Entity.h"
#include <glm/glm.hpp>

namespace shen
{
    glm::vec3 ScreenToWorld(const glm::vec2& screenPos);
    glm::vec2 ObjectWorldPosition2D(Entity entity);
    glm::vec3 RayCastFromMousePos(const glm::vec2& screenPos, const glm::vec2 viewPort, const glm::mat4& proj, const glm::mat4& view);
}
