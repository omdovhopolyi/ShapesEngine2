#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SfmlWindowEndFrameSystem
        : public RenderSystem
    {
    public:
        void Draw() override;
    };
}
