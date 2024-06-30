#include "UITransformComponent.h"
#include "UI/UINode.h"

namespace shen
{
    void UITransformComponent::Init()
    {
        _node->SetTransform(_transform);
    }
}
