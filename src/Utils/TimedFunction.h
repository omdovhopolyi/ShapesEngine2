#pragma once

#include <functional>

namespace shen
{
    enum class TimedFunctionType
    {
        OneShot,
        Update
    };

    class TimedFunction
    {
    public:
        void SetFunc(const std::function<void()>& func, float delay, TimedFunctionType type);
        void Update(float dt);

        void SetUpdateOnStart(bool onStart);
        bool IsUpdateOnStart() const;

        void Reset();
        void Restart();

        float GetCurrentDelay() const;

    private:
        std::function<void()> _func;
        float _delay = 0.f;
        float _currentDelay = 0.f;
        bool _updateOnStart = true;
        TimedFunctionType _type = TimedFunctionType::Update;
    };
}
