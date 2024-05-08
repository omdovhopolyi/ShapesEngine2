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

    void PlayerInput::Load(PlayerInput& component, Serialization& serialization)
    {
        component.commandTypes = serialization.LoadVecStr("array");
    }

    void PlayerInput::Save(Serialization& serialization)
    {

    }

    void Camera::Load(Camera& component, Serialization& serialization)
    {
        component.view.setCenter(serialization.LoadVec2("position"));
        component.view.setViewport(serialization.LoadFloatRect("viewport", sf::FloatRect(0.f, 0.f, 1.f, 1.f)));
        component.view.setSize(serialization.LoadVec2("size"));
        component.view.zoom(serialization.LoadFloat("zoom", 1.f));
        component.view.setRotation(serialization.LoadFloat("rotation"));
    }

    void Camera::Save(Serialization& serialization)
    {

    }
}
