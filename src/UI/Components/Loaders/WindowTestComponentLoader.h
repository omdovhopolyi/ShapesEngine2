#pragma once

#include "WindowComponentBaseLoader.h"

namespace shen
{
    class WindowTestComponentLoader
        : public WindowComponentBaseLoader<WindowTestComponent>
    {
        CLASS_LOADER(UIWindowLoader, WindowTestComponent)
    };
}
