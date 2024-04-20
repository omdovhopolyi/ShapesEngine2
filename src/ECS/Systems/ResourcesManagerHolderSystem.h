#pragma once

#include "BaseSystems/System.h"

namespace shen
{
    class ResourcesManager;

    class ResourcesManagerHolderSystem
        : public System
    {
    public:
        ResourcesManagerHolderSystem(ResourcesManager* resourcesManager);

        ResourcesManager* GetResourcesManager() const;

    private:
        ResourcesManager* _manager = nullptr;
    };
}
