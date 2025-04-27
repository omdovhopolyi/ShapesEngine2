#include "LoadersManager.h"

namespace shen
{
    std::shared_ptr<LoaderBase> LoadersManager::GetLoader(const std::string& type)
    {
        if (auto it = _loaders.find(type); it != _loaders.end())
        {
            return it->second;
        }

        return nullptr;
    }
}
