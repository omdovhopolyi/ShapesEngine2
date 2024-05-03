#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class MovementSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
