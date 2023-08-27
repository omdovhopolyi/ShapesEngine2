#pragma once

#include <chrono>

namespace shen
{
    class Time
    {
    public:
        void Init();
        void Update();
        float Dt() const;

    private:
        float _dt = 0.f;
        std::chrono::steady_clock::time_point _lastUpdateTime;
    };
}
