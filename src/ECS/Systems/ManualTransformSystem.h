#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class ManualTransformSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
