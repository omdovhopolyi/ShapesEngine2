#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class RotationSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
