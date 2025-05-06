#pragma once

namespace shen
{
    class Game;
    class SystemsManager;

    class GameFacade
    {
    public:
        static SystemsManager* GetSystemsManager();
        static void SetGamePtr(Game* game);

    private:
        static Game* _game;
    };
}
