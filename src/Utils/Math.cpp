#include "Math.h"

namespace shen
{
    float SquareLength(const glm::vec3& vec)
    {
        return glm::dot(vec, vec);
    }

    bool FloatEqual(float val1, float val2, float epsilon)
    {
        return glm::abs(val1 - val2) < epsilon;
    }

    glm::vec3 PlaneVectorIntersect(const glm::vec3& planePoint, const glm::vec3& planeNorm, const glm::vec3& rayOrigin, const glm::vec3& rayDirection)
    {
        glm::vec3 worldPos = glm::vec3(0.f);

        float denominator = glm::dot(planeNorm, rayDirection);

        if (glm::abs(denominator) > std::numeric_limits<float>::epsilon())
        {
            float t = glm::dot(glm::vec3(0.f) - rayOrigin, planeNorm) / denominator;
            worldPos = rayOrigin + rayDirection * t;
        }

        return worldPos;
    }
}
