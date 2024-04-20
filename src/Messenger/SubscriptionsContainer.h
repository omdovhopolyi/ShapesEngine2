#pragma once

#include "Messenger.h"

#include <vector>
#include <functional>
#include <memory>
#include <typeinfo>
#include <typeindex>

namespace shen
{
    struct SubscriptionData
    {
        std::type_index typeInde;
        std::shared_ptr<ISubscriptionWrapper> subscription;
    };

    class SubcriptionsContainer
    {
    public:
        ~SubcriptionsContainer();

        template<class TEvent>
        void Subscribe(const std::function<void(const TEvent&)>& callback);

    private:
        std::vector<SubscriptionData> _subscriptions;
    };


    template<class TEvent>
    void SubcriptionsContainer::Subscribe(const std::function<void(const TEvent&)>& callback)
    {
        auto&& subscriptionData = SubscriptionData
        {
            std::type_index(typeid(TEvent)),
            std::make_shared<SubscriptionWrapper<TEvent>>(callback)
        };

        _subscriptions.push_back(std::move(subscriptionData));
        Messenger::Instance().Subscribe<TEvent>(_subscriptions.back().subscription);
    }
}
