#include "SDLSpriteRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/SDLGameWindow.h"
#include "ECS/EcsWorld.h"

#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"

#include "SDL_image.h"
#include <SDL.h>

namespace shen
{
	void SDLSpriteRenderSystem::Draw()
	{
		auto world = ManagersProvider::Instance().GetWorld();

		world->Sort<SDLSprite>([&](const Entity& left, const Entity& right)
		{
			const auto leftTransform = world->GetComponent<Transform>(left);
			const auto rightTransform = world->GetComponent<Transform>(right);
			return leftTransform->position.z < rightTransform->position.z;
		});

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
	}

	void SDLSpriteRenderSystem::Stop()
	{
	}
}
