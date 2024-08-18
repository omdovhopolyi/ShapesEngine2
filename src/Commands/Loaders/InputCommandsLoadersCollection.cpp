#pragma once

#include "InputCommandsLoadersCollection.h"

namespace shen
{
    InputCommandLoader* InputCommandsLoadersCollection::GetLoader(const std::string& type) const
    {
        if (auto it = _loaders.find(type); it != _loaders.end())
        {
            return it->second.get();
        }

        return nullptr;
    }
}
