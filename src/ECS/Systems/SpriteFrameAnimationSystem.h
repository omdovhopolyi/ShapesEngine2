#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class SpriteFrameAnimationSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
