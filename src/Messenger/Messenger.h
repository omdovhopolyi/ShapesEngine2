#pragma once

#include "Events/Event.h"

#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <functional>
#include <list>

namespace shen
{
    class ISubscriptionWrapper
    {
    public:
        virtual ~ISubscriptionWrapper() = default;

        virtual void Execute(const Event& event) = 0;
    };

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

    class Messenger
    {
    public:
        using SubscriptionsList = std::list<std::weak_ptr<ISubscriptionWrapper>>;

        template<class TEvent>
        void Subscribe(const std::weak_ptr<ISubscriptionWrapper>& subscription)
        {
            _subsctiptions[std::type_index(typeid(TEvent))].push_back(subscription);
        }

        template<class TEvent>
        void Broadcast(const TEvent& event)
        {
            auto it = _subsctiptions.find(std::type_index(typeid(TEvent)));
            if (it != _subsctiptions.end())
            {
                for (auto& weakListener : it->second)
                {
                    if (auto listener = weakListener.lock())
                    {
                        listener->Execute(event);
                    }
                }
            }
        }

        void Update();
        void Cleanup();

    private:
        std::map<std::type_index, SubscriptionsList> _subsctiptions;
        std::vector<std::pair<std::type_index, std::weak_ptr<ISubscriptionWrapper>>> _toRemove;
    };
}
