#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class RotationSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(RotationSystem)

    public:
        void Update() override;
    };
}
