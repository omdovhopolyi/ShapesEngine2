#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/CameraFollowSystem.h"
#include "Systems/IntertiaSystem.h"
#include "Systems/BulletSystem.h"
#include "Systems/CleanupSystem.h"

#include "Systems/SDLSystems/SDLTilemapSystem.h"
#include "Systems/SDLSystems/SDLInputSystem.h"
#include "Systems/SDLSystems/SDLAnimatedDirectionSpriteUpdateSystem.h"

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
        manager->RegisterSystem<IntertiaSystem>();
        manager->RegisterSystem<PlayerInputSystem>();
        manager->RegisterSystem<BulletSystem>();
        manager->RegisterSystem<CollisionSystem>();
        manager->RegisterSystem<DamageSystem>();
        manager->RegisterSystem<SDLAnimatedSpriteUpdateSystem>();
        manager->RegisterSystem<SDLAnimatedDirectionSpriteUpdateSystem>();
        manager->RegisterSystem<CameraFollowSystem>();
        manager->RegisterSystem<CleanupSystem>();

        manager->RegisterRenderSystem<SDLTilemapSystem>();
        manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
        manager->RegisterRenderSystem<SDLAnimatedSpriteRenderSystem>();
        manager->RegisterRenderSystem<BoundingBoxDebugSystem>();
    }
}
