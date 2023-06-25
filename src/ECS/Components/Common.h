#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace shen
{
    struct Transform
    {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform(const glm::vec3& pos = {}, float angleZ = 0.f, const glm::vec3& scl = {});
        Transform(const glm::vec3& pos = {}, const glm::quat& rot = {}, const glm::vec3& scl = {});

        float GetEulerAngleZ() const;
    };

    struct RigidBody
    {
        glm::vec3 velocity;

        RigidBody(const glm::vec3& vel = {});
    };
}
