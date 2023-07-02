#include "SDLAnimatedSpriteRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/SDLComponents.h"
#include "ECS/Components/Common.h"

namespace shen
{
	void SDLAnimatedSpriteRenderSystem::Draw()
	{
		auto world = ManagersProvider::Instance().GetWorld();

		world->Each<SDLAnimatedSprite, Transform>(
			[&](auto& entity, SDLAnimatedSprite& sprite, const Transform& transform)
		{
			SDL_Rect sourceRect = {
				sprite.rect.x * frame,
				sprite.rect.y,
				sprite.rect.w,
				sprite.rect.h
			};

			SDL_Rect destRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};	

			SDL_RenderCopyEx(
				_renderer,
				sprite.texture,
				&sourceRect,
				&destRect,
				transform.GetEulerAngleZ(),
				NULL,
				SDL_FLIP_NONE
			);
		});
	}
}
