#pragma once

#include "Utils/Singleton.h"
#include "Resources/AssetsManagerBase.h"

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <map>

namespace shen
{
    class SystemsManager;
    class EcsWorld;
    class Time;
    class GameWindow;
    class AssetsManagerBase;
    class Messenger;
    class WeaponManager;
    class MapLoader;

    class ManagersProvider
        : public Singleton<ManagersProvider>
    {
    public:
        ManagersProvider();
        ~ManagersProvider();

        bool Init();
        void Update();
        void Draw();
        void Clear();

        SystemsManager* GetSystemsManager() const;
        EcsWorld* GetWorld() const;
        Time* GetTime() const;
        GameWindow* GetGameWindow() const;
        Messenger* GetMessenger() const;
        MapLoader* GetMapLoader() const;
        WeaponManager* GetWeaponManager() const;

        template<class T>
        T* GetOrCreateAssetsManager();

    private:
        std::unique_ptr<SystemsManager> _systemsManager;
        std::unique_ptr<EcsWorld> _world;
        std::unique_ptr<Time> _time;
        std::unique_ptr<GameWindow> _gameWindow;
        std::unique_ptr<Messenger> _messenger;
        std::unique_ptr<WeaponManager> _weaponManager;
        std::unique_ptr<MapLoader> _mapLoader;

        std::map<std::type_index, std::unique_ptr<AssetsManagerBase>> _resources;
    };

    template<class T>
    T* ManagersProvider::GetOrCreateAssetsManager()
    {
        const auto typeIndex = std::type_index(typeid(T));
        auto it = _resources.find(typeIndex);
        if (it != _resources.end())
        {
            return static_cast<T*>(it->second.get());
        }
        else
        {
            auto [it, isOk] = _resources.insert({ typeIndex, std::make_unique<T>() });
            if (isOk)
            {
                it->second->Init();
                return static_cast<T*>(it->second.get());
            }
        }

        // TODO assert
        return nullptr;
    }
}
