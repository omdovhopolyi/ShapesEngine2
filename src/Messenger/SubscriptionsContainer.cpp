#include "SubscriptionsContainer.h"

namespace shen
{
    SubcriptionsContainer::~SubcriptionsContainer()
    {
        for (auto& [typeIndex, ptr] : _subscriptions)
        {
            Messenger::Instance().RemoveSubscription(typeIndex, ptr);
        }
    }
}
