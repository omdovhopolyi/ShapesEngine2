#include "Common.h"
#include "Serialization/Serialization.h"
#include "ECS/World.h"

namespace shen
{
    void Transform::Load(Transform& component, const Serialization& serialization)
    {
        component.position = serialization.GetVec2("position");
        component.rotation = serialization.GetFloat("rotation");
        component.scale = serialization.GetVec2("scale", component.scale);
    }

    void Transform::Save(Transform& component, Serialization& serialization)
    {
        serialization.SetVec2("position", component.position);
        serialization.SetFloat("rotation", component.rotation);
        serialization.SetVec2("scale", component.scale);
    }

    void PlayerInput::Load(PlayerInput& component, const Serialization& serialization)
    {
        const auto types = serialization.GetVecStr("input");
        component.commandTypes = { types.begin(), types.end() };
    }

    void PlayerInput::Save(PlayerInput& component, Serialization& serialization)
    {
        serialization.SetVecStr("input", { component.commandTypes.begin(), component.commandTypes.end() });
    }

    void Camera::Load(Camera& component, const Serialization& serialization)
    {
        component.view.setCenter(serialization.GetVec2("position"));
        component.view.setViewport(serialization.GetFloatRect("viewport", sf::FloatRect(0.f, 0.f, 1.f, 1.f)));
        component.view.setRotation(serialization.GetFloat("rotation"));
        component.view.setSize(serialization.GetVec2("size"));
        component.type = serialization.GetStr("cameraType");
    }

    void Camera::Save(Camera& component, Serialization& serialization)
    {
        serialization.SetVec2("position", component.view.getCenter());
        serialization.SetFloatRect("viewport", component.view.getViewport());
        serialization.SetFloat("rotation", component.view.getRotation());
        serialization.SetVec2("size", component.view.getSize());
        serialization.SetStr("cameraType", component.type);
    }
}
