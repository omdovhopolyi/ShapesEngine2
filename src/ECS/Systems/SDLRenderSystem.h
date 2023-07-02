#pragma once

#include "RenderSystem.h"

struct SDL_Renderer;

namespace shen
{
    class SDLGameWindow;

    class SDLRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;

    protected:
        SDLGameWindow* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
    };
}
