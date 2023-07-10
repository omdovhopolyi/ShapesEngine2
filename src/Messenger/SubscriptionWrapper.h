#pragma once

#include "ISubscriptionWrapper.h"
#include <functional>

namespace shen
{
    template<class TEvent>
    class SubscriptionWrapper
        : public ISubscriptionWrapper
    {
    public:
        using Callback = std::function<void(const TEvent&)>;

        SubscriptionWrapper(const Callback& callback) : _callback(callback) {}

        void Execute(const Event& event) override
        {
            Call(static_cast<const TEvent&>(event));
        }

    private:
        void Call(const TEvent& event)
        {
            if (_callback)
            {
                _callback(event);
            }
        }

    private:
        Callback _callback = nullptr;
    };
}
