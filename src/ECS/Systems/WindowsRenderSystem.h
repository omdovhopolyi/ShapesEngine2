#pragma once

#include "BaseSystems/RenderSystem.h"

namespace shen
{
    class WindowsRenderSystem
        : public RenderSystem
    {
    public:
        void Draw() override;
    };
}
