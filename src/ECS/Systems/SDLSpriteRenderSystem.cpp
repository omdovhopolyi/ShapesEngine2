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
		/*auto texturesManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();
		auto world = ManagersProvider::Instance().GetWorld();

		world->Each<SDLSprite>([&](const auto entity, auto& sprite)
		{
			sprite.texture = texturesManager->GetAsset("tank");
			sprite.width = 32;
			sprite.height = 32;
		});*/
	}

    void SDLSpriteRenderSystem::Update()
    {
		SDL_SetRenderDrawColor(_renderer, 21, 21, 21, 255);
		SDL_RenderClear(_renderer);

		auto world = ManagersProvider::Instance().GetWorld();
		world->Each<SDLSprite, Transform>(
			[this](const auto entity, const SDLSprite& sprite, const Transform& transform)
		{
			SDL_Rect destRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};	

			SDL_RenderCopyEx(
				_renderer,
				sprite.texture,
				&sprite.rect,
				&destRect,
				transform.GetEulerAngleZ(),
				NULL,
				SDL_FLIP_NONE
			);
		});

		SDL_RenderPresent(_renderer);
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
