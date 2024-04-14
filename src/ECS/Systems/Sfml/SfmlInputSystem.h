#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace shen
{
    class SfmlInputSyste
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
