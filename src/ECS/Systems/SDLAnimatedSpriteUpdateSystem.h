#pragma once

#include "System.h"

namespace shen
{
    class SDLGameWindow;

    class SDLAnimatedSpriteUpdateSystem
        : public System
    {
    public:
        void Update() override;
    };
}
