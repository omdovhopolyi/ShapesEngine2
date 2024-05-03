#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class SfmlSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Draw();
    };
}
