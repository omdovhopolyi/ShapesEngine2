#include "RotateCommand.h"

#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Game/ManagersProvider.h"
#include "Logger/Logger.h"
#include "Utils/Coords.h"

#include <glm/gtx/vector_angle.hpp>

namespace shen
{
    void RotateCommand::Execute(const Entity& entity, const CommandContext& context) const
    {
        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<PlayerInput, Transform>([&](auto entity, const PlayerInput&, Transform& transform)
        {
            auto mouseScreenPos = glm::vec2(context.x, context.y);
            glm::vec2 mouseWorldPos = ScreenToWorld(mouseScreenPos);
            auto objectWorldPos = ObjectWorldPosition2D(entity);
            auto direction = glm::normalize(mouseWorldPos - objectWorldPos);

            const float angle = glm::degrees(glm::orientedAngle(glm::vec2(1.f, 0.f), direction));
            transform.rotation = glm::angleAxis(glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
        });
        
    }
}
