#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

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
