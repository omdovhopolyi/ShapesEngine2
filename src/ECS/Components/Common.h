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
    };

    struct RigidBody
    {
        glm::vec3 velocity;
    };
}
