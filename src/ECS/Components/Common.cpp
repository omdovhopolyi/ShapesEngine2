#include "Common.h"

#include "Serialization/Serialization.h"
#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"

namespace shen
{
    float Transform::GetEulerAngleZ() const
    {
        return glm::degrees(glm::eulerAngles(rotation).z);
    }

    void Transform::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        auto comp = ManagersProvider::Instance().GetWorld()->AddComponent<Transform>(entity);

        comp->position = LoadVec3("position", element);
        
        const float angle = LoadFloat("rotation", element);
        comp->rotation = glm::angleAxis(glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));

        comp->scale = LoadVec3("scale", element, comp->scale);
        
    }

    void Transform::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    BoundingBox::BoundingBox(const glm::vec3& bbSize, const glm::vec3& bbOffset)
        : size(bbSize)
        , offset(bbOffset)
    {
    }

    void RigidBody::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        ManagersProvider::Instance().GetWorld()->AddComponent<RigidBody>(entity);
    }

    void RigidBody::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    void PlayerInput::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        ManagersProvider::Instance().GetWorld()->AddComponent<PlayerInput>(entity);
    }

    void PlayerInput::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    void Camera::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        auto comp = ManagersProvider::Instance().GetWorld()->AddComponent<Camera>(entity);

        comp->position = LoadVec3("position", element);
        comp->target = LoadVec3("target", element);
        comp->up = LoadVec3("up", element, glm::vec3(0.f, 1.f, 0.f));
        comp->fov = LoadFloat("fov", element, comp->fov);
    }

    void Camera::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    void Sprite::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        auto comp = ManagersProvider::Instance().GetWorld()->AddComponent<Sprite>(entity);

        comp->texture = LoadTexturePtr("texture", element);
        comp->mask = LoadTexturePtr("mask", element);
        comp->texRect = LoadRect("rect", element);
        comp->size = LoadVec2("size", element, comp->size);
        comp->anchor = LoadVec2("anchor", element);
        comp->shader = LoadShaderPtr("shader", element);
    }

    void Sprite::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    void Color::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        auto comp = ManagersProvider::Instance().GetWorld()->AddComponent<Color>(entity);

        comp->rgba = LoadColor("color", element) / 255.f;
    }

    void Color::Save(Entity entity, tinyxml2::XMLElement* element)
    {

    }

    void SpriteFrameAnimation::Load(Entity entity, const tinyxml2::XMLElement* element)
    {
        auto comp = ManagersProvider::Instance().GetWorld()->AddComponent<SpriteFrameAnimation>(entity);

        comp->frameTime = LoadFloat("frameTime", element, comp->frameTime);
        comp->frames = LoadVectorRect("frames", element);
    }

    void SpriteFrameAnimation::Save(Entity entity, tinyxml2::XMLElement* element)
    {
        
    }
}
