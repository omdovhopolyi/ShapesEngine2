#include "Common.h"

namespace shen
{
    Transform::Transform(const glm::vec3& pos, float angleZ, const glm::vec3& scl)
        : position(pos)
        , rotation()
        , scale(scl)
    {
        rotation = glm::angleAxis(glm::radians(angleZ), glm::vec3(0.f, 0.f, 1.f));
    } 

    Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scl)
        : position(pos)
        , rotation(rot)
        , scale(scl)
    {}

    float Transform::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }

    RigidBody::RigidBody(const glm::vec3& vel)
        : velocity(vel)
    {}

    BoundingBox::BoundingBox(const glm::vec3& bbSize, const glm::vec3& bbOffset)
        : size(bbSize)
        , offset(bbOffset)
    {

    }
}
