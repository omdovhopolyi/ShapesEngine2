#pragma once

#include "UIComponentLoader.h"

namespace shen
{
    class UIScreenNormPosTransformComponentLoader
        : public UIComponentLoader
    {
        CLASS_LOADER(UIWindowLoader, UIScreenNormPosTransformComponent)

    public:
        UIComponent* CreateAndLoad(SystemsManager* systems, const std::shared_ptr<UINode>& node, const Serialization& element) override;
    };
}
