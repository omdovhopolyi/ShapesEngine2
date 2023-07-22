#pragma once

#include "System.h"

namespace shen
{
    class CameraFollowSystem
        : public System
    {
    public:
        void Update() override;
    };
}
