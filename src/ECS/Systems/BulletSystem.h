#pragma once

#include "System.h"

namespace shen
{
    class BulletSystem
        : public System
    {
    public:
        void Update() override;
    };
}
