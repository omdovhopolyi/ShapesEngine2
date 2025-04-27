#include "Common.h"
#include "Serialization/DataElementWrapper.h"
#include "ECS/World.h"

namespace shen
{
    void Transform::Load(Transform& component, const DataElementWrapper& elementWrapper)
    {
        component.position = elementWrapper.GetVec2("position");
        component.rotation = elementWrapper.GetFloat("rotation");
        component.scale = elementWrapper.GetVec2("scale", component.scale);
    }

    void Transform::Save(Transform& component, DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetVec2("position", component.position);
        elementWrapper.SetFloat("rotation", component.rotation);
        elementWrapper.SetVec2("scale", component.scale);
    }

    void PlayerInput::Load(PlayerInput& component, const DataElementWrapper& elementWrapper)
    {
        const auto types = elementWrapper.GetVecStr("input");
        component.commandTypes = { types.begin(), types.end() };
    }

    void PlayerInput::Save(PlayerInput& component, DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetVecStr("input", { component.commandTypes.begin(), component.commandTypes.end() });
    }

    void Camera::Load(Camera& component, const DataElementWrapper& elementWrapper)
    {
        component.view.setCenter(elementWrapper.GetVec2("position"));
        component.view.setViewport(elementWrapper.GetFloatRect("viewport", sf::FloatRect(0.f, 0.f, 1.f, 1.f)));
        component.view.setRotation(elementWrapper.GetFloat("rotation"));
        component.view.setSize(elementWrapper.GetVec2("size"));
        component.type = elementWrapper.GetStr("cameraType");
    }

    void Camera::Save(Camera& component, DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetVec2("position", component.view.getCenter());
        elementWrapper.SetFloatRect("viewport", component.view.getViewport());
        elementWrapper.SetFloat("rotation", component.view.getRotation());
        elementWrapper.SetVec2("size", component.view.getSize());
        elementWrapper.SetStr("cameraType", component.type);
    }
}
