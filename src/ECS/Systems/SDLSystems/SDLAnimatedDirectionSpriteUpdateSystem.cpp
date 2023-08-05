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

		world->Each<SpriteAnimationDirection, SDLAnimatedSprite, RigidBody>(
			[&](const auto entity, const SpriteAnimationDirection& spriteDir, SDLAnimatedSprite& sprite, const RigidBody& rb)
		{
            const bool hasDirection = SquareLength(rb.direction);
            if (hasDirection)
            {
                const auto direction2d = glm::vec2(rb.direction.x, rb.direction.y);
                const float angle = glm::degrees(glm::orientedAngle(_forward, direction2d));

                int offsetCoef = spriteDir.backwardSourceOffset;

                auto directionComp = world->GetOrCreateComponent<Direction>(entity);

                if (_forwardAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.forwardSourceOffset;
                    directionComp->vec = glm::vec3(0.f, -1.f, 0.f);
                }
                else if (_rightAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.rightSourceOffset;
                    directionComp->vec = glm::vec3(1.f, 0.f, 0.f);
                }
                else if (_leftAngleRange.IsInRange(angle))
                {
                    offsetCoef = spriteDir.leftSourceOffset;
                    directionComp->vec = glm::vec3(-1.f, 0.f, 0.f);
                }
                else
                {
                    directionComp->vec = glm::vec3(0.f, 1.f, 0.f);
                }

                sprite.rect.y = sprite.rect.h * offsetCoef;
            }
		});
	}
}
