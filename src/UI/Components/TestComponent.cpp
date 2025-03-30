#include "TestComponent.h"
#include "Serialization/Types/SerializableFieldInt.h"
#include "Serialization/Types/SerializableFieldFloat.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "Serialization/Types/SerializableFieldAsset.h"

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
