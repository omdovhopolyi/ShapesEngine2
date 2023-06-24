#pragma once

#include "System.h"

class SDL_Renderer;

namespace shen
{
    class SDLGameWindow;

    class SDLSpriteRenderSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;

    private:
        SDLGameWindow* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
    };
}
