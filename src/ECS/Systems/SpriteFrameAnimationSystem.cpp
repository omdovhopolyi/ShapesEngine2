#include "SpriteFrameAnimationSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Components/Render.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Rendering.h"

namespace shen
{
	REGISTER_SYSTEMS_FACTORY(SpriteFrameAnimationSystem)

    void SpriteFrameAnimationSystem::Update()
    {
		auto& world = _systems->GetWorld();
		auto time = _systems->GetSystem<TimeSystem>();

		world.Each<SpriteFrameAnimation, Sprite>(
			[&](const auto entity, SpriteFrameAnimation& animation, Sprite& sprite)
		{
			animation.dt += time->Dt();
			const int framesForward = static_cast<int>(animation.dt / animation.frameTime);
			if (framesForward > 0)
			{
				animation.dt = 0.f;
			}

			const auto prevFrame = animation.curFrame;

			animation.curFrame += framesForward;
			animation.curFrame %= static_cast<int>(animation.frames.size());

			if (animation.curFrame != prevFrame)
			{
				sprite.sprite.setTextureRect(animation.frames[animation.curFrame]);
			}
		});
    }
}
