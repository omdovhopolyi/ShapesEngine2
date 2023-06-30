#pragma once

#include "RenderSystem.h"

class SDL_Renderer;

namespace shen
{
    class SDLGameWindow;

    class SDLSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;
        void Stop() override;

    private:
        SDLGameWindow* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
    };
}
