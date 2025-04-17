#pragma once

#include "UIComponent.h"
#include "Serialization/LoaderMacro.h"

namespace shen
{
    class UIWindowComponent
        : public UIComponent
    {
        CLASS_LOADER_TEST(UIWindowComponent)

    public:
        void Close();
    };
}
