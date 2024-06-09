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

    void Transform::Save(Transform& component, Serialization& serialization)
    {
        serialization.SaveVec2("position", component.position);
        serialization.SaveFloat("rotation", component.rotation);
        serialization.SaveVec2("scale", component.scale);
    }

    void PlayerInput::Load(PlayerInput& component, Serialization& serialization)
    {
        component.commandTypes = serialization.LoadVecStr("array");
    }

    void PlayerInput::Save(PlayerInput& component, Serialization& serialization)
    {
        serialization.SaveVecStr("array", component.commandTypes);
    }

    void Camera::Load(Camera& component, Serialization& serialization)
    {
        component.view.setCenter(serialization.LoadVec2("position"));
        component.view.setViewport(serialization.LoadFloatRect("viewport", sf::FloatRect(0.f, 0.f, 1.f, 1.f)));
        //component.view.zoom(serialization.LoadFloat("zoom", 1.f));
        component.view.setRotation(serialization.LoadFloat("rotation"));
        component.view.setSize(serialization.LoadVec2("size"));

        /*auto size = serialization.LoadVec2("size");
        size.y *= -1;
        component.view.setSize(size);*/
    }

    void Camera::Save(Camera& component, Serialization& serialization)
    {
        serialization.SaveVec2("position", component.view.getCenter());
        serialization.SaveFloatRect("viewport", component.view.getViewport());
        serialization.SaveFloat("rotation", component.view.getRotation());
        serialization.SaveVec2("size", component.view.getSize());

        /*auto size = component.view.getSize();
        size.y *= -1;
        serialization.SaveVec2("size", size);*/
    }
}
