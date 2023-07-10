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
        void Subscribe(const SubscriptionWeakPtr& subscription)
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

        void RemoveSubscription(std::type_index typeIndex, const SubscriptionWeakPtr& ptr);
        void Update();
        void Cleanup();

    private:
        std::map<std::type_index, SubscriptionsList> _subsctiptions;
        std::vector<std::pair<std::type_index, SubscriptionWeakPtr>> _toRemove;
    };
}
