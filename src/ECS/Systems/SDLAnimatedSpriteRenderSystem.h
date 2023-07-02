#pragma once

#include "RenderSystem.h"

namespace shen
{
    class SDLAnimatedSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Draw() override;
    };
}
