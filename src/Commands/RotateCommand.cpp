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

            static glm::vec3 up{ 0.f, 0.f, 1.f };
            static glm::vec2 right{ 1.f, 0.f };

            const float angle = glm::degrees(glm::orientedAngle(right, direction));
            transform.rotation = glm::angleAxis(glm::radians(angle), up);
        });
        
    }
}
