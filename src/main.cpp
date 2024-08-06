
#ifndef SHEN_NO_MAIN

#include "Game/Game.h"

int main(int argc, char* argv[])
{
    shen::Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}

#endif
