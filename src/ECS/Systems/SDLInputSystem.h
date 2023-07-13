#pragma once

#include "System.h"

namespace shen
{
    class SDLInputSystem
        : public System
    {
    public:
        void Update() override;
    };
}
