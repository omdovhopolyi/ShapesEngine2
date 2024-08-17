#pragma once

#include "UIWindowComponent.h"
#include "UIButtonComponent.h"
#include <memory>

namespace shen
{
    class WindowTestComponent
        : public UIWindowComponent
    {
        friend class WindowTextComponentLoader;

    public:
        WindowTestComponent();

        void Init() override;

    private:
        std::weak_ptr<UIComponent> _button;
    };
}
