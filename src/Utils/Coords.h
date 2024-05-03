#pragma once

#include "ECS/Entity.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    sf::Vector2f ScreenToWorld(const sf::Vector2f& screenPos);
    sf::Vector2f ObjectWorldPosition2D(Entity entity);
    //glm::vec3 RayCastFromMousePos(const glm::vec2& screenPos, const glm::vec2 viewPort, const glm::mat4& proj, const glm::mat4& view);
}
