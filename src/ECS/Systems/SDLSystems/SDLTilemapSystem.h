#pragma once

#include "SDLRenderSystem.h"
#include <vector>

#include <glm/glm.hpp>

struct SDL_Texture;

namespace shen
{
    struct TilemapCell
    {
        int x = -1;
        int y = -1;
    };

    class SDLTilemapSystem
        : public SDLRenderSystem
    {
    public:
        void Start() override;
        void Draw() override;
        void Stop() override;

        glm::vec2 GetTilemapSize() const;

    private:
        bool ReadTilemap();
        void CreateTilemapTexture();
        void FillTilemapTexture();

    private:
        SDL_Texture* _tilemapTex = nullptr;

        std::vector<std::vector<TilemapCell>> _tilemapCells;

        // TODO config
        int _tileWidth = 32;
        int _tileHeight = 32;
        float _tileScale = 1.f;

        int _tilemapWidth = 0;
        int _tilemapHeight = 0;
    };
}
