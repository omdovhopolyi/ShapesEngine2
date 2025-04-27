#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class SpriteFrameAnimationSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(SpriteFrameAnimationSystem)

    public:
        void Update() override;
    };
}
