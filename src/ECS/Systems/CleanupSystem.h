#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CleanupSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(CleanupSystem)

    public:
        void Update() override;
    };
}
