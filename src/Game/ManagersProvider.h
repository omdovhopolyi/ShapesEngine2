#pragma once

#include "Utils/Singleton.h"
#include <memory>

namespace shen
{
    class SystemsManager;
    class EcsWorld;
    class Time;
    class GameWindow;

    class ManagersProvider
        : public Singleton<ManagersProvider>
    {
    public:
        ManagersProvider();
        ~ManagersProvider();

        bool Init();
        void Update();
        void Clear();

        SystemsManager* GetSystemsManager() const;
        EcsWorld* GetWorld() const;
        Time* GetTime() const;
        GameWindow* GetGameWindow() const;

    private:
        std::unique_ptr<SystemsManager> _systemsManager;
        std::unique_ptr<EcsWorld> _world;
        std::unique_ptr<Time> _time;
        std::unique_ptr<GameWindow> _gameWindow;
    };
}
