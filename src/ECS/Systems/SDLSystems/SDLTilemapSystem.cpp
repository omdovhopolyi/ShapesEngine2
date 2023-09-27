#include "SDLTilemapSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/SDLGameWindow.h"
#include "Game/Camera.h"
#include "Resources/SDLTexturesManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"

//#include <SDL_image.h>
#include <SDL.h>
#include <sstream>
#include <fstream>

namespace shen
{
    void SDLTilemapSystem::Start()
    {
		SDLRenderSystem::Start();

		if (_renderer)
		{
			if (ReadTilemap())
			{
				CreateTilemapTexture();
				FillTilemapTexture();

				ManagersProvider::Instance().GetCamera()->SetWorldSize(GetTilemapSize());
			}
		}
    }

	void SDLTilemapSystem::Draw()
	{
		auto camera = ManagersProvider::Instance().GetCamera();
		auto cameraPosition = camera->GetPosition();

		SDL_Rect sourceRect = {
			0,
			0,
			_tilemapWidth,
			_tilemapHeight
		};

		SDL_Rect destRect = {
			static_cast<int>(-cameraPosition.x),
			static_cast<int>(-cameraPosition.y),
			static_cast<int>(_tilemapWidth),
			static_cast<int>(_tilemapHeight)
		};	

		SDL_RenderCopyEx(_renderer, _tilemapTex, &sourceRect, &destRect, 0, NULL, SDL_FLIP_NONE);
	}

    void SDLTilemapSystem::Stop()
    {
    }

	glm::vec2 SDLTilemapSystem::GetTilemapSize() const
	{
		return glm::vec2(_tilemapWidth, _tilemapHeight);
	}

	bool SDLTilemapSystem::ReadTilemap()
	{
		_tilemapCells.clear();

		std::ifstream mapFile;
		mapFile.open("../assets/tilemaps/jungle.map");
		if (mapFile.is_open())
		{
			std::string line;
			while (std::getline(mapFile, line))
			{
				char charX;
				char charY;
				std::stringstream ss(line);

				std::vector<TilemapCell> row;

				while (ss >> charX >> charY)
				{
					if (std::isdigit(charX) && std::isdigit(charY))
					{
						int x = std::atoi(&charX);
						int y = std::atoi(&charY);

						row.push_back({ x, y });

						ss.get();
					}
					else
					{
						// TODO asset
						mapFile.close();
						return false;
					}
				}

				_tilemapCells.push_back(std::move(row));
			}
		}
		else
		{
			// TODO assert
			mapFile.close();
			return false;
		}

		mapFile.close();
		return true;
	}

	void SDLTilemapSystem::CreateTilemapTexture()
	{
		_tilemapWidth = static_cast<int>(_tilemapCells.begin()->size()) * _tileWidth;
		_tilemapHeight = static_cast<int>(_tilemapCells.size()) * _tileHeight;

		SDL_DestroyTexture(_tilemapTex);
		_tilemapTex = nullptr;

		_tilemapTex = SDL_CreateTexture(
			_renderer, 
			SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_TARGET, 
			_tilemapWidth, 
			_tilemapHeight
		);
	}

	void SDLTilemapSystem::FillTilemapTexture()
	{
		if (!_tilemapTex)
		{
			// TODO assert
			return;
		}

		auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		auto tilesAtlas = texturesManager->GetAsset("tilemap");

		SDL_SetRenderTarget(_renderer, _tilemapTex);
		SDL_RenderClear(_renderer);

		for (int i = 0; i < static_cast<int>(_tilemapCells.size()); i++)
		{
			const auto& row = _tilemapCells[i];

			for (int j = 0; j < static_cast<int>(row.size()); j++)
			{
				const auto& cell = row[j];

				const float posX = j * _tileWidth;
				const float posY = i * _tileHeight;

				SDL_Rect sourceRect;
				sourceRect.x = _tileWidth * cell.y;
				sourceRect.y = _tileHeight * cell.x;
				sourceRect.w = 32;
				sourceRect.h = 32;

				SDL_Rect destRect;
				destRect.x = j * _tileWidth;
				destRect.y = i * _tileHeight;
				destRect.w = _tileWidth;
				destRect.h = _tileHeight;

				SDL_RenderCopyEx(
					_renderer,
					tilesAtlas,
					&sourceRect,
					&destRect,
					0.f,
					NULL,
					SDL_FLIP_NONE
				);
			}
		}

		SDL_SetRenderTarget(_renderer, NULL);
	}
}
