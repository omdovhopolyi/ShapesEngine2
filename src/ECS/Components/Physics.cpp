#include "Physics.h"
#include "ECS/World.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    void RigidBody::Load(RigidBody& component, const DataElementWrapper& elementWrapper)
    {
        component.type = RigidBodyTypeEnum.FromString(elementWrapper.GetStr("bodyType"));
        component.size = elementWrapper.GetVec2("size", component.size);
        component.sensor = elementWrapper.GetBool("sensor", component.sensor);
    }

    void RigidBody::Save(RigidBody& component, DataElementWrapper& elementWrapper)
    {
        const auto typeStr = RigidBodyTypeEnum.ToString(component.type);
        elementWrapper.SetStr("bodyType", typeStr);
        elementWrapper.SetVec2("size", component.size);
        elementWrapper.SetBool("sensor", component.sensor);
    }
}
