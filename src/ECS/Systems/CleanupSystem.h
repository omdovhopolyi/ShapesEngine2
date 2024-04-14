#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CleanupSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
