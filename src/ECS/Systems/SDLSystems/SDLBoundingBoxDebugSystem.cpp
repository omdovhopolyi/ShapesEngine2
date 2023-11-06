#include "SDLBoundingBoxDebugSystem.h"

#include "Game/ManagersProvider.h"
#include "Game/Camera.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

#include "Messenger/Events/Common.h"

#include <SDL.h>

namespace shen
{
    void SDLBoundingBoxDebugSystem::Start()
    {
        SDLRenderSystem::Start();
        Subscribe();
    }

    void SDLBoundingBoxDebugSystem::Draw()
    {
        if (!_isActivated)
        {
            return;
        }

        auto world = ManagersProvider::Instance().GetWorld();
        //auto camera = ManagersProvider::Instance().GetCamera();

        world->Each<BoundingBox, Transform>(
            [&](auto entity, const BoundingBox& bb, const Transform& transform)
        {
            auto origin = transform.position + bb.offset;

            SDL_Rect rect;
            //rect.x = origin.x - camera->GetPosition().x;
            //rect.y = origin.y - camera->GetPosition().y;
            rect.w = bb.size.x * transform.scale.x;
            rect.h = bb.size.y * transform.scale.y;

            Uint8 r, g, b, a;
            SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(_renderer, &rect);
            SDL_SetRenderDrawColor(_renderer, r, g, b, a);
        });
    }

    void SDLBoundingBoxDebugSystem::Subscribe()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.type == KeyEventType::Up)
            {
                if (event.code == SDLK_f)
                {
                    _isActivated = !_isActivated;
                }
            }
        });
    }
}
