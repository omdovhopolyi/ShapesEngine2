#include "Math.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

namespace shen
{
    float Length(const sf::Vector2f& vec)
    {
        return std::sqrt(SquareLength(vec));
    }

    float SquareLength(const sf::Vector2f& vec)
    {
        return DotProduct(vec, vec);
    }

    bool FloatEqual(float val1, float val2, float epsilon)
    {
        return std::abs(val1 - val2) < epsilon;
    }

    /*glm::vec3 PlaneVectorIntersect(const glm::vec3& planePoint, const glm::vec3& planeNorm, const glm::vec3& rayOrigin, const glm::vec3& rayDirection)
    {
        glm::vec3 worldPos = glm::vec3(0.f);

        float denominator = glm::dot(planeNorm, rayDirection);

        if (glm::abs(denominator) > std::numeric_limits<float>::epsilon())
        {
            float t = glm::dot(glm::vec3(0.f) - rayOrigin, planeNorm) / denominator;
            worldPos = rayOrigin + rayDirection * t;
        }

        return worldPos;
    }*/

    float Radians(float degrees)
    {
        return degrees * M_PI / 180.f;
    }

    float Degrees(float radians)
    {
        return radians * 180.f / M_PI;
    }

    sf::Vector2f Normalize(const sf::Vector2f& vec)
    {
        const float length = Length(vec);
        return sf::Vector2f(vec.x / length, vec.y / length);
    }

    float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    float Angle(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
    {
        return std::acos(DotProduct(vec1, vec2));
    }

    float OrientedAngle(const sf::Vector2f& vec)
    {
        return std::atan2(vec.y, vec.x);
    }

    float OrientedAngle(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
    {
        const auto atanVec1 = OrientedAngle(vec1);
        const auto atanVec2 = OrientedAngle(vec2);
        return atanVec1 - atanVec2;
    }
}
