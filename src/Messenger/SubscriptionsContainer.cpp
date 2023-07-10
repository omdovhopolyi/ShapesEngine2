#include "SubscriptionsContainer.h"

namespace shen
{
    SubcriptionsContainer::~SubcriptionsContainer()
    {
        auto messenger = ManagersProvider::Instance().GetMessenger();

        for (auto& [typeIndex, ptr] : _subscriptions)
        {
            messenger->RemoveSubscription(typeIndex, ptr);
        }
    }
}
