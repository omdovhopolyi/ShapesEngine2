#pragma once

#include "ECS/Systems/System.h"

namespace shen
{
    class SDLAnimatedSpriteUpdateSystem
        : public System
    {
    public:
        void Update() override;
    };
}
