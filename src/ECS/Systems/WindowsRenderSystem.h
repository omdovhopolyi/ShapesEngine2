#pragma once

#include "BaseSystems/RenderSystem.h"

namespace shen
{
    class WindowsRenderSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(WindowsRenderSystem)

    public:
        void Draw() override;
    };
}
