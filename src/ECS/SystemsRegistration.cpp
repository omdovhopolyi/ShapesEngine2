#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"

#include "Systems/SDLSystems/SDLTilemapSystem.h"
#include "Systems/SDLSystems/SDLInputSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/SDLSystems/SDLAnimatedDirectionSpriteUpdateSystem.h"
#include "Systems/CameraFollowSystem.h"

#include "Systems/SDLSystems/SDLSpriteRenderSystem.h"
#include "Systems/SDLSystems/SDLAnimatedSpriteUpdateSystem.h"
#include "Systems/SDLSystems/SDLAnimatedSpriteRenderSystem.h"
#include "Systems/SDLSystems/BoundingBoxDebugSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto manager = ManagersProvider::Instance().GetSystemsManager();

        manager->RegisterSystem<SDLInputSystem>();
        manager->RegisterSystem<MovementSystem>();
        manager->RegisterSystem<CameraFollowSystem>();
        manager->RegisterSystem<CollisionSystem>();
        manager->RegisterSystem<SDLAnimatedSpriteUpdateSystem>();
        manager->RegisterSystem<SDLAnimatedDirectionSpriteUpdateSystem>();
        manager->RegisterSystem<DamageSystem>();
        manager->RegisterSystem<PlayerInputSystem>();

        manager->RegisterRenderSystem<SDLTilemapSystem>();
        manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
        manager->RegisterRenderSystem<SDLAnimatedSpriteRenderSystem>();
        manager->RegisterRenderSystem<BoundingBoxDebugSystem>();
    }
}
