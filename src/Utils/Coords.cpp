#include "Coords.h"

#include "Game/ManagersProvider.h"
#include "Game/GameWindow.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Render.h"
#include "Math.h"

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

        auto viewport = glm::vec2{ winWidth, winHeight };

        auto ray = RayCastFromMousePos(screenPos, viewport, camera->projection, camera->view);
        auto worldPos = PlaneVectorIntersect(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), camera->position, ray);
        return worldPos;
    }

    glm::vec2 ObjectWorldPosition2D(Entity entity)
    {
        glm::vec2 result{ 0.f };

        const auto world = ManagersProvider::Instance().GetWorld();

        if (auto transform = world->GetComponent<Transform>(entity))
        {
            result = transform->position;
        }

        return result;
    }

    glm::vec3 RayCastFromMousePos(const glm::vec2& screenPos, const glm::vec2 viewport, const glm::mat4& proj, const glm::mat4& view)
    {
        const float x = 2.f * screenPos.x / viewport.x - 1.f;
        const float y = 1.f - (2.f * screenPos.y / viewport.y);

        auto ray4 = glm::vec4(x, y, -1.f, 1.f);
        ray4 = glm::inverse(proj) * ray4;
        ray4.w = 0.f;
        glm::vec3 ray = glm::inverse(view) * ray4;
        ray = glm::normalize(ray);

        return ray;
    }
}
