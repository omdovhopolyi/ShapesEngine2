#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class IntertiaSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
