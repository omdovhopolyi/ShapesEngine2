#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace shen
{
    class SfmlWindowBeginFrameSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
