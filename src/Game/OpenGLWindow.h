#pragma once

#include "GameWindow.h"
#include <SDL.h>

namespace shen
{
    class OpenGLWindow
        : public GameWindow
    {
    public:
        bool Init() override;
        void Destroy() override;

        void BeginFrame() override;
        void EndFrame() override;

        SDL_Window* GetWindow() const { return _window; }
       // SDL_Renderer* GetRenderer() const { return _renderer; }

    private:
        SDL_Window* _window = nullptr;
        SDL_GLContext _glContext = nullptr;
        //SDL_Renderer* _renderer = nullptr;
    };
}
