#include "Messenger.h"

namespace shen
{
    void Messenger::Update()
    {

    }

    void Messenger::Cleanup()
    {
        for (auto& [type, ptr] : _toRemove)
        {
            auto it = _subsctiptions.find(type);
            if (it != _subsctiptions.end())
            {
                it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [&](const auto& val)
                {
                    return val.lock() == ptr.lock();
                }));
            }
        }

        _toRemove.clear();
    }
}
