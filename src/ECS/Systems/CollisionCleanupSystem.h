#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CollisionCleanupSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(CollisionCleanupSystem)

    public:
        void Update() override;
    };
}
