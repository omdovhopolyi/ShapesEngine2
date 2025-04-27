#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class MovementSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(MovementSystem)

    public:
        void Update() override;
    };
}
