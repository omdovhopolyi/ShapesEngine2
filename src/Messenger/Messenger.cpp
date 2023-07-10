#include "Messenger.h"

namespace shen
{
    void Messenger::RemoveSubscription(std::type_index typeIndex, const SubscriptionWeakPtr& ptr)
    {
        auto it = _subsctiptions.find(typeIndex);
        if (it != _subsctiptions.end())
        {
            it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [&](const auto& val)
            {
                return val.lock() == ptr.lock();
            }));
        }

        if (it->second.empty())
        {
            _subsctiptions.erase(typeIndex);
        }
    }

    void Messenger::Update()
    {

    }

    void Messenger::Cleanup()
    {
        for (auto& [type, ptr] : _toRemove)
        {
            RemoveSubscription(type, ptr);
        }

        _toRemove.clear();
    }
}
