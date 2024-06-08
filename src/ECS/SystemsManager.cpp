#include "SystemsManager.h"

namespace shen
{
    void SystemsManager::Init(Game* game)
    {
        _game = game;
    }

    void SystemsManager::Start()
    {
        for (auto& system : _registrationOrderedSystems)
        {
            system->Start();
        }
    }

    void SystemsManager::Update()
    {
        for (auto& system : _updateSystems)
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
        for (auto& system : _registrationOrderedSystems)
        {
            system->Stop();
        }
    }

    void SystemsManager::Clear()
    {
        Logger::Log("SystemsManager::Clear");
        _updateSystems.clear();
        _renderSystems.clear();
        _mappedSystems.clear();
        _registrationOrderedSystems.clear();
        _world.Clear();
    }
}
