#pragma once

#include "ECS/Systems/System.h"

namespace shen
{
    class SpriteFrameAnimationSystem
        : public System
    {
    public:
        void Update() override;
    };
}
