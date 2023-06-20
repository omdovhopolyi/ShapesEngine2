#include "SDLSpriteRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/GameWindow.h"
#include "ECS/EcsWorld.h"

#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"

#include "SDL_image.h"
#include <SDL.h>

namespace shen
{
	void SDLSpriteRenderSystem::Start()
	{
		// TODO Object creation
		
		auto renderer = ManagersProvider::Instance().GetGameWindow()->GetRenderer();
		auto world = ManagersProvider::Instance().GetWorld();

		world->Each<SDLSprite>([renderer](const auto entity, auto& sprite)
		{
			SDL_Surface* surface = IMG_Load("../assets/images/tank-panther-right.png");

			sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);
			sprite.width = 32;
			sprite.height = 32;

			SDL_FreeSurface(surface);
		});
	}

    void SDLSpriteRenderSystem::Update()
    {
		auto world = ManagersProvider::Instance().GetWorld();
		auto renderer = ManagersProvider::Instance().GetGameWindow()->GetRenderer();

		world->Each<SDLSprite, Transform>(
			[renderer](const auto entity, const auto& sprite, const auto& transform)
		{
			SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
			SDL_RenderClear(renderer);

			SDL_Rect destRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				sprite.width,
				sprite.height
			};	

			SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);

			//SDL_DestroyTexture(texture);
			SDL_RenderPresent(renderer);
		});
    }

	void SDLSpriteRenderSystem::Stop()
	{
		// TODO Object destroing

		auto world = ManagersProvider::Instance().GetWorld();
		world->Each<SDLSprite>([](const auto entity, auto& sprite)
		{
			SDL_DestroyTexture(sprite.texture);
		});
	}
}
