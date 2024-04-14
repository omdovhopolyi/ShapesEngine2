#include "ResourcesManager.h"

namespace shen
{
    ResourcesManager::ResourcesManager() = default;
    ResourcesManager::~ResourcesManager() = default;

    bool ResourcesManager::Init()
    {
        for (auto& [index, assetsManager] : _resources)
        {
            assetsManager->Init();
        }

        return true;
    }

    void ResourcesManager::Clear()
    {
        for (auto& [index, assetsManager] : _resources)
        {
            assetsManager->Clear();
        }

        _resources.clear();
    }
}
