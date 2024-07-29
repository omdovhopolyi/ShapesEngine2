#pragma once

#include "UIComponent.h"
//#include "UIWindowComponent.h"
#include "UIButtonComponent.h"
#include <memory>

namespace shen
{
    class WindowTestComponent
        //: public UIWindowComponent
        : public UIComponent
    {
        friend class WindowTextComponentLoader;

    public:
        WindowTestComponent();

        void Init() override;

    private:
        std::weak_ptr<UIComponent> _button;
    };
}
