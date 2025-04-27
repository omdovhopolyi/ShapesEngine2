#include "TimedFunction.h"

namespace shen
{
    void TimedFunction::SetFunc(const std::function<void()>& func, float delay, TimedFunctionType type)
    {
        _func = func;
        _delay = delay;
        _currentDelay = _delay;
        _type = type;
    }

    void TimedFunction::Update(float dt)
    {
        if (_func)
        {
            if (_currentDelay <= 0.f)
            {
                _func();

                if (_type == TimedFunctionType::OneShot)
                {
                    Reset();
                }
                else if (_type == TimedFunctionType::Update)
                {
                    Restart();
                }
            }
            else
            {
                _currentDelay -= dt;
            }
        }
    }

    void TimedFunction::SetUpdateOnStart(bool onStart)
    {
        _updateOnStart = onStart;
    }

    bool TimedFunction::IsUpdateOnStart() const
    {
        return _updateOnStart;
    }

    void TimedFunction::Reset()
    {
        _func = nullptr;
        _delay = 0.f;
        _currentDelay = 0.f;
        _type = TimedFunctionType::Update;
    }

    void TimedFunction::Restart()
    {
        _currentDelay = _delay;
    }

    float TimedFunction::GetCurrentDelay() const
    {
        return _currentDelay;
    }
}
