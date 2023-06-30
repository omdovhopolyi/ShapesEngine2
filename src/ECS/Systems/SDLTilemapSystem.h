#pragma once

#include "RenderSystem.h"
#include <vector>

class SDL_Renderer;
struct SDL_Texture;

namespace shen
{
    class SDLGameWindow;

    struct TilemapCell
    {
        int x = -1;
        int y = -1;
    };

    class SDLTilemapSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;
        void Stop() override;

    private:
        bool ReadTilemap();
        void CreateTilemapTexture();
        void FillTilemapTexture();

    private:
        SDLGameWindow* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        SDL_Texture* _tilemapTex = nullptr;

        std::vector<std::vector<TilemapCell>> _tilemapCells;

        // TODO config
        int _tileWidth = 32;
        int _tileHeight = 32;
        float _tileScale = 2.f;

        int _tilemapWidth = 0;
        int _tilemapHeight = 0;
    };
}
