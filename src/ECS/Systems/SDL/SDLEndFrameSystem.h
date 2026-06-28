#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SDLEndFrameSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SDLEndFrameSystem)

    public:
        void Draw() override;
    };
}
