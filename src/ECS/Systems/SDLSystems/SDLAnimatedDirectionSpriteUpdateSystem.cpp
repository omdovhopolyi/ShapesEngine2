#include "SDLAnimatedDirectionSpriteUpdateSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/Time.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"
#include "Utils/Math.h"

#include <glm/gtx/vector_angle.hpp>

namespace shen
{
	void SDLAnimatedDirectionSpriteUpdateSystem::Update()
	{
		auto world = ManagersProvider::Instance().GetWorld();
		const float dt = ManagersProvider::Instance().GetTime()->Dt();

		world->Each<SDLSpriteAnimationDirection, SDLAnimatedSprite, RigidBody>(
			[&](const auto entity, const SDLSpriteAnimationDirection& spriteDir, SDLAnimatedSprite& sprite, const RigidBody& rb)
		{
            const bool hasVelocity = SquareLength(rb.velocity);
            if (hasVelocity)
            {
                const auto velocity2d = glm::vec2(rb.velocity.x, rb.velocity.y);
                const float angle = glm::degrees(glm::orientedAngle(_forward, glm::normalize(velocity2d)));

                int offsetCoef = spriteDir.backwardSourceOffset;

                if (_forwardAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.forwardSourceOffset;
                }
                else if (_rightAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.rightSourceOffset;
                }
                else if (_leftAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.leftSourceOffset;
                }

                sprite.rect.y = sprite.rect.h * offsetCoef;
            }
		});
	}
}
