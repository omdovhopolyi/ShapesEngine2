#include "UITransformComponent.h"
#include "UI/UINode.h"
#include "Serialization/Types/SerializableFieldTransform.h"
#include "Serialization/Types/SerializableFieldVec2.h"

namespace shen
{
    REGISTER_LOADER(UITransformComponent);

    void UITransformComponent::RegisterProperties()
    {
        UIComponent::RegisterProperties();

        RegisterVar<SerializableFieldTransform>(_transform, "transform");
        RegisterVar<SerializableFieldVec2>(_anchor, "anchor");
    }

    void UITransformComponent::Init()
    {
        _node->SetTransform(_transform);
    }
}
