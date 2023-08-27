#include "Game/Game.h"

#include "sol/sol.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    /*sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math);
    lua.script_file("../assets/scripts/test.lua");

    int var = lua["testVar"];
    std::cout << var << std::endl;*/

    shen::Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
