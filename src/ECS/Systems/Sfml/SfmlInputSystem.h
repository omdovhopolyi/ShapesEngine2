#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace shen
{
    class SfmlInputSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
