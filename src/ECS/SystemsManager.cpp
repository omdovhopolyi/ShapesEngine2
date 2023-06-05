#include "SystemsManager.h"
#include "SystemsRegistration.h"

namespace shen
{
    void SystemsManager::Init()
    {
        RegisterSystems();
    }

    void SystemsManager::Start()
    {
        for (auto& system : _systems)
        {
            system->Start();
        }
    }

    void SystemsManager::Update()
    {
        for (auto& system : _systems)
        {
            system->Update();
        }
    }

    void SystemsManager::Stop()
    {
        for (auto& system : _systems)
        {
            system->Stop();
        }
    }

    void SystemsManager::Clear()
    {
        _systems.clear();
        _mappedSystems.clear();
    }
}
