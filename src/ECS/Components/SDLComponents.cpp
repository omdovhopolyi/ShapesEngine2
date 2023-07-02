#include "SDLComponents.h"

namespace shen
{
    SDLSprite::SDLSprite(SDL_Texture* tex, int w, int h, int sourceX, int sourceY, int sourceW, int sourceH)
        : texture(tex)
        , width(w)
        , height(h)
    {
        rect.x = sourceX;
        rect.y = sourceY;
        rect.w = sourceW;
        rect.h = sourceH;
    }

    SDLAnimatedSprite::SDLAnimatedSprite(SDL_Texture* tex, int w, int h, int sourceX, int sourceY, int sourceW, int sourceH)
        : SDLSprite(tex, w, h, sourceX, sourceY, sourceW, sourceH)   
    {
    }

    void SDLAnimatedSprite::InitAtimation(int frames, int framesPerSec)
    {
        numFrames = frames;
        frameTime = 1.f / framesPerSec;
    }
}
