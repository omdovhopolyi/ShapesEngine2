#include "Physics.h"
#include "ECS/World.h"
#include "Serialization/DataElementWrapper.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "Serialization/Types/SerializableFieldBool.h"
#include "Serialization/Types/SerializableFieldVec2.h"

namespace shen
{
    REGISTER_LOADER(RigidBody)

    void RigidBody::RegisterProperties()
    {
        RegisterVar<SerializableFieldString>(_typeStr, "bodyType");
        RegisterVar<SerializableFieldVec2>(size, "size");
        RegisterVar<SerializableFieldBool>(sensor, "sensor");
    }

    void RigidBody::AfterLoad()
    {
        SetType(_typeStr);
    }

    RigidBodyType RigidBody::GetType() const
    {
        return _type;
    }

    void RigidBody::SetType(RigidBodyType type)
    {
        _type = type;
        _typeStr = RigidBodyTypeEnum.ToString(_type);
        
    }

    void RigidBody::SetType(const std::string& typeStr)
    {
        _typeStr = typeStr;
        _type = RigidBodyTypeEnum.FromString(_typeStr);
    }
}
