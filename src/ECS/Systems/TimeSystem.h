#pragma once

#include "BaseSystems/UpdateSystem.h"

#include <chrono>

namespace shen
{
    class TimeSystem
        : public UpdateSystem
    {
    public:
        void Start();
        void Update();
        float Dt() const;

    private:
        float _dt = 0.f;
        std::chrono::steady_clock::time_point _lastUpdateTime;
    };
}
