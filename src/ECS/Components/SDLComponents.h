#pragma once

#include <SDL.h>

namespace shen
{
    struct SDLSprite
    {
        SDL_Texture* texture = nullptr;
        int width = 0;
        int height = 0;
        SDL_Rect rect;
    };
}
