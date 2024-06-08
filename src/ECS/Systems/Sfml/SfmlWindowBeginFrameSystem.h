#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SfmlWindowBeginFrameSystem
        : public RenderSystem
    {
    public:
        void Draw() override;
    };
}
