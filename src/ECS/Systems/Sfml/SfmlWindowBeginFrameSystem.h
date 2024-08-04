#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SfmlWindowBeginFrameSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SfmlWindowBeginFrameSystem)

    public:
        void Draw() override;
    };
}
