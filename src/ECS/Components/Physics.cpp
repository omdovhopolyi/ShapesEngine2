#include "Physics.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void RigidBody::Load(RigidBody& component, const Serialization& serialization)
    {
        component.type = RigidBodyTypeEnum.FromString(serialization.GetStr("type"));
        component.size = serialization.GetVec2("size", component.size);
        component.sensor = serialization.GetBool("sensor", component.sensor);
    }

    void RigidBody::Save(RigidBody& component, Serialization& serialization)
    {
        const auto typeStr = RigidBodyTypeEnum.ToString(component.type);
        serialization.SetStr("type", typeStr);
        serialization.SetVec2("size", component.size);
        serialization.SetBool("sensor", component.sensor);
    }
}
