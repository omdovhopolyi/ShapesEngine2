#include "SystemsManager.h"

namespace shen
{
    void SystemsManager::Init()
    {
    }

    void SystemsManager::Start()
    {
        for (auto& system : _systems)
        {
            system->Start();
        }

        for (auto& system : _renderSystems)
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

    void SystemsManager::Draw()
    {
        for (auto& system : _renderSystems)
        {
            system->Draw();
        }
    }

    void SystemsManager::Stop()
    {
        for (auto& system : _systems)
        {
            system->Stop();
        }

        for (auto& system : _renderSystems)
        {
            system->Stop();
        }
    }

    void SystemsManager::Clear()
    {
        Logger::Log("SystemsManager::Clear");
        _systems.clear();
        _renderSystems.clear();
        _mappedSystems.clear();
    }
}
