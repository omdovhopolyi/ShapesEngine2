#pragma once

#include <glm/glm.hpp>
#include <limits>

namespace shen
{
    float SquareLength(const glm::vec3& vec);
    bool FloatEqual(float val1, float val2, float epsilon = std::numeric_limits<float>::epsilon());
    glm::vec3 PlaneVectorIntersect(const glm::vec3& planePoint, const glm::vec3& planeNorm, const glm::vec3& rayOrigin, const glm::vec3& rayDirection);
    float Radians(float degrees);
    float Degrees(float radians);
}
