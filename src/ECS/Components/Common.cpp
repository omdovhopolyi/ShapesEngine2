#include "Common.h"
#include "Serialization/Serialization.h"
#include "ECS/World.h"

namespace shen
{
    void Transform::Load(Transform& component, Serialization& serialization)
    {
        component.position = serialization.LoadVec2("position");
        component.rotation = serialization.LoadFloat("rotation");
        component.scale = serialization.LoadVec2("scale", component.scale);
    }

    void Transform::Save(Serialization& serialization)
    {

    }

    void Mover::Load(Mover& component, Serialization& serialization)
    {
    }

    void Mover::Save(Serialization& serialization)
    {

    }

    /*float Rotator::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }*/

    void PlayerInput::Load(PlayerInput& component, Serialization& serialization)
    {
        component.commandTypes = serialization.LoadVecStr("array");
    }

    void PlayerInput::Save(Serialization& serialization)
    {

    }

    void Camera::Load(Camera& component, Serialization& serialization)
    {
    }

    void Camera::Save(Serialization& serialization)
    {

    }
}
