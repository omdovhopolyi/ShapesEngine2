#include "SpriteFrameAnimationSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/Time.h"
#include "ECS/World.h"
#include "ECS/Components/Render.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Rendering.h"

namespace shen
{
    void SpriteFrameAnimationSystem::Update()
    {
		auto world = ManagersProvider::Instance().GetWorld();
		const float dt = ManagersProvider::Instance().GetTime()->Dt();

		world->Each<SpriteFrameAnimation, Sprite>(
			[&](const auto entity, SpriteFrameAnimation& animation, Sprite& sprite)
		{
			animation.dt += dt;
			const int framesForward = static_cast<int>(animation.dt / animation.frameTime);
			if (framesForward > 0)
			{
				animation .dt = 0.f;
			}

			const auto prevFrame = animation.curFrame;

			animation.curFrame += framesForward;
			animation.curFrame %= static_cast<int>(animation.frames.size());

			if (animation.curFrame != prevFrame)
			{
				sprite.texRect = animation.frames[animation.curFrame];

				ManagersProvider::Instance().GetMessenger()->Broadcast<UpdateTexRect>(entity, sprite.texRect);
			}
		});
    }
}
