#pragma once

#include "RenderSystem.h"

struct SDL_Renderer;

namespace shen
{
    class SDLGameWindow;

    class SDLAnimatedSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;

    private:
        SDLGameWindow* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
    };
}
