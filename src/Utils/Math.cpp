#include "Math.h"

namespace shen
{
    float SquareLength(const glm::vec3& vec)
    {
        return glm::dot(vec, vec);
    }
}
