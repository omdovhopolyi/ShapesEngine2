#pragma once

#include "System.h"

namespace shen
{
    class RenderSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;
    };
}
