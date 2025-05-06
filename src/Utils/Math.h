#pragma once

#include <SFML/System/Vector2.hpp>
#include <limits>

namespace shen
{
    float Length(const sf::Vector2f& vec);
    float SquareLength(const sf::Vector2f& vec);
    bool FloatEqual(float val1, float val2, float epsilon = std::numeric_limits<float>::epsilon());
    bool FloatZero(float val, float epsilon = std::numeric_limits<float>::epsilon());
    float Radians(float degrees);
    float Degrees(float radians);
    sf::Vector2f Normalize(const sf::Vector2f& vector);
    float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    float Angle(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    float OrientedAngle(const sf::Vector2f& vec);
    float OrientedAngle(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    int RandomInt(int min, int max);
    float RandomFloat(float min, float max);
    sf::Vector2f Rotate(const sf::Vector2f& vec, float angle);
    void RotateThis(sf::Vector2f& vec, float angle);
    //glm::vec3 PlaneVectorIntersect(const glm::vec3& planePoint, const glm::vec3& planeNorm, const glm::vec3& rayOrigin, const glm::vec3& rayDirection);
}
