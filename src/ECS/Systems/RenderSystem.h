#pragma once

#include "BaseSystem.h"

namespace shen
{
    class RenderSystem
        : public BaseSystem
    {
    public:
        virtual void Start();
        virtual void Draw();
        virtual void Stop();
    };
}
