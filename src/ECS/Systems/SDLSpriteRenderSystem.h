#pragma once

#include "System.h"

namespace shen
{
    class SDLSpriteRenderSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;
    };
}
