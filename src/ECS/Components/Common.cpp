#include "Common.h"
#include "Serialization/DataElementWrapper.h"
#include "Serialization/Types/SerializableFieldVec2.h"
#include "Serialization/Types/SerializableFieldFloat.h"
#include "Serialization/Types/SerializableFieldSetStr.h"
#include "Serialization/Types/SerializableFieldViewport.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "ECS/World.h"

namespace shen
{
    REGISTER_LOADER(Transform)

    void Transform::RegisterProperties()
    {
        RegisterVar<SerializableFieldVec2>(position, "position");
        RegisterVar<SerializableFieldFloat>(rotation, "rotation");
        RegisterVar<SerializableFieldVec2>(scale, "scale");
    }

    REGISTER_LOADER(PlayerInput)

    void PlayerInput::RegisterProperties()
    {
        RegisterVar<SerializableFieldSetStr>(commandTypes, "input");
    }

    REGISTER_LOADER(Camera)

    void Camera::RegisterProperties()
    {
        RegisterVar<SerializableFieldViewport>(view, "viewport");
        RegisterVar<SerializableFieldString>(type, "viewport");
    }
}
