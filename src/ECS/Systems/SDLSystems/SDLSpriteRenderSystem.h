#pragma once

#include "SDLRenderSystem.h"

namespace shen
{
    class SDLSpriteRenderSystem
        : public SDLRenderSystem
    {
    public:
        void Draw() override;
        void Stop() override;
    };
}
