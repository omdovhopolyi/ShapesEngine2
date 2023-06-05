#pragma once

#include "Utils/Singleton.h"

namespace shen
{
    const int FPS = 60;
    const int MILLISEC_PER_FRAME = 1000 / FPS;

    class Time
        : public Singleton<Time>
    {
    public:
        void Init();
        void Update();

        float Dt() const;

    private:
        int _lastUpdateTime = 0;
        float _dt = 0.f;
    };
}
