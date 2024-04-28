#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace shen
{
    class SfmlWindowEndFrameSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
