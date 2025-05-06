#include "GameFacade.h"
#include "Game.h"

namespace shen
{
    Game* GameFacade::_game = nullptr;

    SystemsManager* GameFacade::GetSystemsManager()
    {
        return _game->_systems.get();
    }

    void GameFacade::SetGamePtr(Game* game)
    {
        _game = game;
    }
}
