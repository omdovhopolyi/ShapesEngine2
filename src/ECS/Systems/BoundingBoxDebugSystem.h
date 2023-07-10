#pragma once

#include "SDLRenderSystem.h"

namespace shen
{
    class BoundingBoxDebugSystem
        : public SDLRenderSystem
    {
    public:
        void Draw() override;
    };
}
