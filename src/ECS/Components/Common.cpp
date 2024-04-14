#include "Common.h"
#include "Serialization/Serialization.h"
#include "ECS/World.h"

namespace shen
{
    float Transform::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }

    void Transform::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<Transform>(entity);

        comp->position = LoadVec3("position", element);
        
        const float angle = LoadFloat("rotation", element);
        comp->rotation = glm::angleAxis(glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));

        comp->scale = LoadVec3("scale", element, comp->scale);
        
    }

    void Transform::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }

    void Mover::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        world->AddComponent<Mover>(entity);
    }

    void Mover::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }

    float Rotator::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }

    void PlayerInput::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<PlayerInput>(entity);

        comp->commandTypes = LoadVecStr("array", element);
    }

    void PlayerInput::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }

    void Camera::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<Camera>(entity);

        comp->position = LoadVec3("position", element);
        comp->target = LoadVec3("target", element);
        comp->up = LoadVec3("up", element, glm::vec3(0.f, 1.f, 0.f));
        comp->fov = LoadFloat("fov", element, comp->fov);
    }

    void Camera::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }
}
