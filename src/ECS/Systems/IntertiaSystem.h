#pragma once

#include "System.h"

namespace shen
{
    class IntertiaSystem
        : public System
    {
    public:
        void Update() override;
    };
}
