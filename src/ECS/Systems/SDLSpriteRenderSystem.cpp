#include "SDLSpriteRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/SDLGameWindow.h"
#include "ECS/EcsWorld.h"

#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"
#include "Resources/SDLTexturesManager.h"

#include "SDL_image.h"
#include <SDL.h>

namespace shen
{
	void SDLSpriteRenderSystem::Start()
	{
		auto window = ManagersProvider::Instance().GetGameWindow();

		if (_window = dynamic_cast<SDLGameWindow*>(window))
		{
			_renderer = _window->GetRenderer();
		}

		if (!_renderer)
		{
			return;
		}

		// TODO Object creation
		auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		auto world = ManagersProvider::Instance().GetWorld();

		world->Each<SDLSprite>([&](const auto entity, auto& sprite)
		{
			sprite.texture = texturesManager->GetAsset("tank");
			sprite.width = 32;
			sprite.height = 32;
		});
	}

    void SDLSpriteRenderSystem::Update()
    {
		auto world = ManagersProvider::Instance().GetWorld();
		world->Each<SDLSprite, Transform>(
			[&](const auto entity, const auto& sprite, const auto& transform)
		{
			SDL_SetRenderDrawColor(_renderer, 21, 21, 21, 255);
			SDL_RenderClear(_renderer);

			SDL_Rect destRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				sprite.width,
				sprite.height
			};	

			SDL_RenderCopy(_renderer, sprite.texture, NULL, &destRect);

			SDL_RenderPresent(_renderer);
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
