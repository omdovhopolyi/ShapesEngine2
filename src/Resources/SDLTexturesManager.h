#pragma once

#include "AssetsManager.h"

#include <SDL.h>

namespace shen
{
    class SDLTexturesManager final
        : public AssetsManager<SDL_Texture*>
    {
    public:
        bool Init() override;
        void Clear() override;

    protected:
        std::pair<SDL_Texture*, bool> LoadAssetImpl(const std::string& path) override;

    private:
        SDL_Renderer* _renderer = nullptr;
    };
}
