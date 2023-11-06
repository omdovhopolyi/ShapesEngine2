#include "ManagersProvider.h"
#include "ECS/SystemsManager.h"
#include "ECS/EcsWorld.h"
#include "Time.h"
#include "GameWindow.h"
#include "SDLGameWindow.h"
#include "OpenGLWindow.h"
//#include "Camera.h"
#include "Messenger/Messenger.h"
#include "Game/WeaponManager.h"
#include "Game/MapLoader.h"

namespace shen
{
    ManagersProvider::ManagersProvider() = default;
    ManagersProvider::~ManagersProvider() = default;

    bool ManagersProvider::Init()
    {
        _gameWindow = nullptr;
        //_gameWindow = std::make_unique<SDLGameWindow>();
        _gameWindow = std::make_unique<OpenGLWindow>();

        if (_gameWindow)
        {
            if (_gameWindow->Init())
            {
                _messenger = std::make_unique<Messenger>();
                _systemsManager = std::make_unique<SystemsManager>();
                _world = std::make_unique<EcsWorld>();
                _time = std::make_unique<Time>();
                _mapLoader = std::make_unique<MapLoader>();
                _weaponManager = std::make_unique<WeaponManager>();

                _mapLoader->RegisterLoaders();
                _systemsManager->Init();
                _time->Init();

                for (auto& [index, assetsManager] : _resources)
                {
                    assetsManager->Init();
                }

                return true;
            }
        }

        return false;
    }

    void ManagersProvider::Update()
    {
        _time->Update();
        _systemsManager->Update();
    }

    void ManagersProvider::Draw()
    {
        _gameWindow->BeginFrame();
        _systemsManager->Draw();
        _gameWindow->EndFrame();
    }

    void ManagersProvider::Clear()
    {
        _systemsManager->Stop();
        _systemsManager->Clear();
        _world->Clear();
        _gameWindow->Destroy();
    }

    SystemsManager* ManagersProvider::GetSystemsManager() const
    {
        return _systemsManager.get();
    }

    EcsWorld* ManagersProvider::GetWorld() const
    {
        return _world.get();
    }

    Time* ManagersProvider::GetTime() const
    {
        return _time.get();
    }

    GameWindow* ManagersProvider::GetGameWindow() const
    {
        return _gameWindow.get();
    }

    Messenger* ManagersProvider::GetMessenger() const
    {
        return _messenger.get();
    }

    MapLoader* ManagersProvider::GetMapLoader() const
    {
        return _mapLoader.get();
    }

    WeaponManager* ManagersProvider::GetWeaponManager() const
    {
        return _weaponManager.get();
    }
}
