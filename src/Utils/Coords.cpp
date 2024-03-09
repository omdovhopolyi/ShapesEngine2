#include "Coords.h"

#include "Game/ManagersProvider.h"
#include "Game/GameWindow.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    glm::vec3 ScreenToWorld(const glm::vec2& screenPos)
    {
        const auto window = ManagersProvider::Instance().GetGameWindow();
        const auto world = ManagersProvider::Instance().GetWorld();

        Camera* camera = nullptr;

        auto cameraEntity = world->GetFirst<Camera>();
        if (world->IsValid(cameraEntity))
        {
            camera = world->GetComponent<Camera>(cameraEntity);
        }

        if (!camera)
        {
            return glm::vec3(screenPos.x, screenPos.y, 0.f);
        }

        const int winWidth = window->GetWidth();
        const int winHeight = window->GetHeight();

        const float x = 2.f * screenPos.x / winWidth - 1.f;
        const float y = 1.f - (2.f * screenPos.y / winHeight);

        auto transformMat = camera->projection * camera->view;
        auto inverseMat = glm::inverse(transformMat);
        auto worldPos = inverseMat * glm::vec4(x, y, 0.f, 1.f);
        worldPos.x *= worldPos.w;
        worldPos.y *= worldPos.w;

        return glm::vec3(worldPos.x, worldPos.y, worldPos.z);
    }

    glm::vec2 ObjectWorldPosition2D(Entity entity)
    {
        glm::vec2 result{ 0.f };

        const auto world = ManagersProvider::Instance().GetWorld();

        if (auto transform = world->GetComponent<Transform>(entity))
        {
            glm::vec3 anchorOffset{};

            if (auto sprite = world->GetComponent<Sprite>(entity))
            {
                anchorOffset = glm::vec3(sprite->size, 0.f) * glm::vec3(sprite->anchor, 0.f);
            }

            //result = transform->position + anchorOffset;
        }

        return result;
    }
}
