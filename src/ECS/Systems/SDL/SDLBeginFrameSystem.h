#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SDLBeginFrameSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SDLBeginFrameSystem)

    public:
        void Draw() override;
    };
}
