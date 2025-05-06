
#ifndef SHEN_NO_MAIN

#include "Game/Game.h"
#include "Game/GameFacade.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    shen::Game game;
    shen::GameFacade::SetGamePtr(&game);

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}

#endif
