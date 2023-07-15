#include "SDLAnimatedSpriteUpdateSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/Time.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/SDLComponents.h"

namespace shen
{
	void SDLAnimatedSpriteUpdateSystem::Update()
	{
		auto world = ManagersProvider::Instance().GetWorld();
		const float dt = ManagersProvider::Instance().GetTime()->Dt();

		world->Each<SDLAnimatedSprite>(
			[&](const auto entity, SDLAnimatedSprite& sprite)
		{
			sprite.dt += dt;
			const int framesForward = static_cast<int>(sprite.dt / sprite.frameTime);
			if (framesForward > 0)
			{
				sprite.dt = 0.f;
			}

			sprite.curFrame += framesForward;
			sprite.curFrame %= sprite.numFrames;
		});
	}
}
