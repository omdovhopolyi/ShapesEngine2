#include "Common.h"
#include "Serialization/Serialization.h"
#include "ECS/World.h"

namespace shen
{
    /*float Transform::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }*/

    void Transform::Load(Entity entity, World& world, const tinyxml2::XMLElement* element)
    {
        auto comp = world.AddComponent<Transform>(entity);

        comp->position = LoadVec2("position", element);
        comp->rotation = LoadFloat("rotation", element);
        comp->scale = LoadVec2("scale", element, comp->scale);
    }

    void Transform::Save(Entity entity, World& world, tinyxml2::XMLElement* element)
    {

    }

    void Mover::Load(Entity entity, World& world, const tinyxml2::XMLElement* element)
    {
        world.AddComponent<Mover>(entity);
    }

    void Mover::Save(Entity entity, World& world, tinyxml2::XMLElement* element)
    {

    }

    /*float Rotator::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }*/

    void PlayerInput::Load(Entity entity, World& world, const tinyxml2::XMLElement* element)
    {
        auto comp = world.AddComponent<PlayerInput>(entity);

        comp->commandTypes = LoadVecStr("array", element);
    }

    void PlayerInput::Save(Entity entity, World& world, tinyxml2::XMLElement* element)
    {

    }

    void Camera::Load(Entity entity, World& world, const tinyxml2::XMLElement* element)
    {
    }

    void Camera::Save(Entity entity, World& world, tinyxml2::XMLElement* element)
    {

    }
}
