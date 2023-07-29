#pragma once

#include "System.h"

namespace shen
{
    class CleanupSystem
        : public System
    {
    public:
        void Update() override;
    };
}
