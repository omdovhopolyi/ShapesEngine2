#include "Physics.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void RigidBody::Load(RigidBody& component, Serialization& serialization)
    {
        component.type = RigidBodyTypeEnum.FromString(serialization.LoadStr("type"));
        component.size = serialization.LoadVec2("size", component.size);
        component.sensor = serialization.LoadBool("sensor", component.sensor);
    }

    void RigidBody::Save(RigidBody& component, Serialization& serialization)
    {
        const auto typeStr = RigidBodyTypeEnum.ToString(component.type);
        serialization.SaveStr("type", typeStr);
        serialization.SaveVec2("size", component.size);
        serialization.SaveBool("sensor", component.sensor);
    }
}
