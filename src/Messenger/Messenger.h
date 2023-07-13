#pragma once

#include "SubscriptionWrapper.h"

#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <list>

namespace shen
{
    class Messenger
    {
    public:
        using SubscriptionWeakPtr = std::weak_ptr<ISubscriptionWrapper>;
        using SubscriptionsList = std::list<std::weak_ptr<ISubscriptionWrapper>>;

        template<class TEvent>
        void Subscribe(const SubscriptionWeakPtr& subscription);

        template<class TEvent>
        void Broadcast();

        template<class TEvent>
        void Broadcast(const TEvent& event);

        template<class TEvent, class ...Args>
        void Broadcast(Args... args);

        void RemoveSubscription(std::type_index typeIndex, const SubscriptionWeakPtr& ptr);
        void Update();
        void Cleanup();

    private:
        std::map<std::type_index, SubscriptionsList> _subsctiptions;
        std::vector<std::pair<std::type_index, SubscriptionWeakPtr>> _toRemove;
    };

    template<class TEvent>
    void Messenger::Subscribe(const SubscriptionWeakPtr& subscription)
    {
        _subsctiptions[std::type_index(typeid(TEvent))].push_back(subscription);
    }

    template<class TEvent>
    void Messenger::Broadcast()
    {
        Broadcast<TEvent>(TEvent{});
    }

    template<class TEvent>
    void Messenger::Broadcast(const TEvent& event)
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

    template<class TEvent, class ...Args>
    void Messenger::Broadcast(Args... args)
    {
        TEvent event{ std::forward<Args>(args)... };
        Broadcast<TEvent>(event);
    }
}
