#include "SubscriptionsContainer.h"

namespace shen
{
    SubcriptionsContainer::~SubcriptionsContainer()
    {
        Reset();
    }

    void SubcriptionsContainer::Reset()
    {
        for (auto& [typeIndex, ptr] : _subscriptions)
        {
            Messenger::Instance().RemoveSubscription(typeIndex, ptr);
        }

        _subscriptions.clear();
    }
}
