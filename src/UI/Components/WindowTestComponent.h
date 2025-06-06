#pragma once

#include "UIWindowComponent.h"
#include "UIButtonComponent.h"
#include <memory>

namespace shen
{
    class WindowTestComponent
        : public UIWindowComponent
    {
        SERIALIZABLE(WindowTestComponent)

    public:
        void Init() override;
        void RegisterReferences() override;

    private:
        UIComponentWrapper<UIButtonComponent> _button;
    };
}
