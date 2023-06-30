#pragma once

#include "BaseSystem.h"

namespace shen
{
    class System
        : public BaseSystem
    {
    public:
        virtual ~System() = default;

        virtual void Start() {};
        virtual void Update() {};
        virtual void Stop() {};
    };
}
