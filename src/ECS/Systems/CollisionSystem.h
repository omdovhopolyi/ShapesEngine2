#pragma once

#include "System.h"

namespace shen
{
    class CollisionSystem
        : public System
    {
    public:
        void Update() override;
    };
}
