#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <imgui.h>
#include <sol/sol.hpp>
#include <glm/glm.hpp>

int main(int argc, char *argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_EVERYTHING);

    glm::vec2 vel = glm::vec2(0.f);

    sol::state lua;
    lua.open_libraries(sol::lib::base);

    std::cout << "Hello, Shapes Engine 2" << std::endl;
    
    return 0;
}