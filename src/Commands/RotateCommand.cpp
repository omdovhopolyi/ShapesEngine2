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
        auto rotator = world->GetOrCreateComponent<Rotator>(entity);

        auto mouseScreenPos = glm::vec2(context.x, context.y);
        glm::vec3 mouseWorldPos = ScreenToWorld(mouseScreenPos);

        Logger::Log("Mouse world pos {} {} {}", mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);

        glm::vec2 mouseWorldPos2D = mouseWorldPos;

        auto objectWorldPos = ObjectWorldPosition2D(entity);
        auto direction = glm::normalize(mouseWorldPos2D - objectWorldPos);

        static glm::vec3 up{ 0.f, 0.f, 1.f };
        static glm::vec2 right{ 1.f, 0.f };

        const float angle = glm::degrees(glm::orientedAngle(right, direction));
        rotator->rotation = glm::angleAxis(glm::radians(angle), up);        
    }
}
