#pragma once

namespace shen
{
    struct Event;

    class ISubscriptionWrapper
    {
    public:
        virtual ~ISubscriptionWrapper() = default;

        virtual void Execute(const Event& event) = 0;
    };
}
