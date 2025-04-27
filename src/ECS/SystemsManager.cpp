#include "SystemsManager.h"
#include "Systems/Basesystems/RenderSystem.h"
#include "Systems/BaseSystems/UpdateSystem.h"
#include "Systems/TimeSystem.h"
#include "Messenger/Events/Common.h"

namespace shen
{
    void SystemsManager::Init(Game* game)
    {
        _game = game;
        InitSubscriptions();
    }

    void SystemsManager::AddSystem(std::unique_ptr<System>&& system)
    {
        system->Init(this);

        _mappedSystems[system->GetTypeIndex()] = system.get();
        _registrationOrderedSystems.push_back(system.get());

        if (auto timeSystem = dynamic_cast<TimeSystem*>(system.get()))
        {
            _timeSystem = timeSystem;
        }

        if (dynamic_cast<RenderSystem*>(system.get()))
        {
            RenderSystem* renderSystem = static_cast<RenderSystem*>(system.release());
            _renderSystems.push_back(std::unique_ptr<RenderSystem>(renderSystem));
            Logger::Log(std::format("Register {} render system", renderSystem->GetTypeName()));
        }
        else if (dynamic_cast<UpdateSystem*>(system.get()))
        {
            UpdateSystem* updateSystem = static_cast<UpdateSystem*>(system.release());
            _updateSystems.push_back(std::unique_ptr<UpdateSystem>(updateSystem));
            Logger::Log(std::format("Register {} update system", updateSystem->GetTypeName()));
        }
        else
        {
            Logger::Log(std::format("Register {} simple system", system->GetTypeName()));
            _simpleSystems.push_back(std::move(system));
        }
    }

    void SystemsManager::Load()
    {
        for (auto& system : _registrationOrderedSystems)
        {
            system->Load();
        }
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

    void SystemsManager::Save()
    {
        for (auto& system : _registrationOrderedSystems)
        {
            system->Save();
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

    void SystemsManager::InitSubscriptions()
    {
        _subscriptions.Reset();

        _subscriptions.Subscribe<LostFocus>([this](const auto&)
        {
            OnLostFocus();
        });

        _subscriptions.Subscribe<GainedFocus>([this](const auto&)
        {
            OnGainedFocus();
        });
    }

    void SystemsManager::OnLostFocus()
    {
        for (auto system : _registrationOrderedSystems)
        {
            system->AppDeactivated();
        }
    }

    void SystemsManager::OnGainedFocus()
    {
        for (auto system : _registrationOrderedSystems)
        {
            system->AppActivated();
        }
    }
}
