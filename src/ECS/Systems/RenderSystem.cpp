#include "RenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/GameWindow.h"
#include "ECS/EcsWorld.h"

#include "ECS/Components/Transform.h"

#include "SDL_image.h"
#include <SDL.h>

namespace shen
{
	void RenderSystem::Start()
	{

	}

    void RenderSystem::Update()
    {
		auto world = ManagersProvider::Instance().GetWorld();

		world->Each<Transform>(
			[](const auto entity, const auto& transform)
		{
			auto renderer = ManagersProvider::Instance().GetGameWindow()->GetRenderer();

			SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
			SDL_RenderClear(renderer);

			SDL_Surface* surface = IMG_Load("../assets/images/tank-panther-right.png");
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			SDL_Rect destRect = { 
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				32, 
				32 
			};	

			SDL_RenderCopy(renderer, texture, NULL, &destRect);

			SDL_DestroyTexture(texture);
			SDL_RenderPresent(renderer);
		});
    }

	void RenderSystem::Stop()
	{

	}
}
