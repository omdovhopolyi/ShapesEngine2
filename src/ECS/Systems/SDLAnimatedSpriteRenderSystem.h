#pragma once

#include "SDLRenderSystem.h"

namespace shen
{
    class SDLAnimatedSpriteRenderSystem
        : public SDLRenderSystem
    {
    public:
        void Draw() override;
    };
}
