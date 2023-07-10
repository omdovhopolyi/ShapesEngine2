#include "BoundingBoxDebugSystem.h"

#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

#include <SDL.h>

namespace shen
{
    void BoundingBoxDebugSystem::Draw()
    {
        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<BoundingBox, Transform>(
            [&](auto entity, const BoundingBox& bb, const Transform& transform)
        {
            auto origin = transform.position + bb.offset;

            SDL_Rect rect;
            rect.x = origin.x;
            rect.y = origin.y;
            rect.w = bb.size.x * transform.scale.x;
            rect.h = bb.size.y * transform.scale.y;

            Uint8 r, g, b, a;
            SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(_renderer, &rect);
            SDL_SetRenderDrawColor(_renderer, r, g, b, a);
        });
    }
}
