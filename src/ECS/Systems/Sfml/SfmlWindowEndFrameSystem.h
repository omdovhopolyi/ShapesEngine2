#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SfmlWindowEndFrameSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SfmlWindowEndFrameSystem)

    public:
        void Draw() override;
    };
}
