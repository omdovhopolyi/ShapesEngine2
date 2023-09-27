#include "SDLTexturesManager.h"
#include "Game/ManagersProvider.h"
#include "Game/SDLGameWindow.h"

//#include <SDL_image.h>
#include <SDL.h>

namespace shen
{
    bool SDLTexturesManager::Init()
    {
        if (auto gameWindow = ManagersProvider::Instance().GetGameWindow())
        {
            if (auto sdlWindow = dynamic_cast<SDLGameWindow*>(gameWindow))
            {
                _renderer = sdlWindow->GetRenderer();
            }
        }

        return _renderer ? true : false;
    }

    void SDLTexturesManager::Clear()
    {
        for (auto& [id, texture] : _assets)
        {
            SDL_DestroyTexture(texture);
        }

        _assets.clear();
    }

    std::pair<SDL_Texture*, bool> SDLTexturesManager::LoadAssetImpl(const std::string& path)
    {
        /*if (auto texture = IMG_LoadTexture(_renderer, path.c_str()))
        {
            return { texture, true };
        }*/

        return { nullptr, false };
    }
}
