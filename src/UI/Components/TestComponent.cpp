#include "TestComponent.h"
#include "Serialization/Types/SerializedTypeInt.h"
#include "Serialization/Types/SerializedTypeFloat.h"
#include "Serialization/Types/SerializedTypeString.h"
#include "Serialization/Types/SerializedTypeAsset.h"

namespace shen
{
    REGISTER_CLASS_LOADER_TEST(UITestComponent)

    UITestComponent::UITestComponent()
    {
        RegisterVar<SerializableFieldInt>(_intVal, "intVal");
        RegisterVar<SerializableFieldFloat>(_floatVal, "floatVal");
        RegisterVar<SerializableFieldString>(_stringVal, "stringVal");
        RegisterVar<SerializableFieldAsset<UITestComponent>>(_componentVal, "componentVal");
    }
}
