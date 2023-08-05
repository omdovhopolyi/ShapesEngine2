#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

namespace shen
{
    struct SDLSprite
    {
        SDL_Texture* texture = nullptr;
        int width = 0;
        int height = 0;
        SDL_Rect rect;

        SDLSprite(SDL_Texture* tex, int w, int h, int sourceX, int sourceY, int sourceW, int sourceH);
    };

    struct SDLAnimatedSprite
        : SDLSprite
    {
        float dt = 0.f;
        float frameTime = 1.f;
        int numFrames = 1;
        int curFrame = 0;
        
        SDLAnimatedSprite(SDL_Texture* tex, int w, int h, int sourceX, int sourceY, int sourceW, int sourceH);
        void InitAtimation(int frames, int framesPerSec);
    };
}
