#include "ResourcesManagerHolderSystem.h"

namespace shen
{
    ResourcesManagerHolderSystem::ResourcesManagerHolderSystem(ResourcesManager* resourcesManager)
        : System()
        , _manager(resourcesManager)
    {}

    ResourcesManager* ResourcesManagerHolderSystem::GetResourcesManager() const
    {
        return _manager;
    }
}
