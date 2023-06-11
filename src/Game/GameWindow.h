#pragma once

#include <SDL.h>

namespace shen
{
    class GameWindow
    {
    public:
        bool Init();
        void Destroy();

        // TODO
        SDL_Window* GetWindow() const { return _window; }
        SDL_Renderer* GetRenderer() const { return _renderer; }

    private:
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        int _winWidth = 800;
        int _winHeight = 600;
    };
}
