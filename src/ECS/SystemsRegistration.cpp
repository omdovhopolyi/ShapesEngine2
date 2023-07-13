#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/SDLTilemapSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/SDLInputSystem.h"

#include "Systems/SDLSpriteRenderSystem.h"
#include "Systems/SDLAnimatedSpriteUpdateSystem.h"
#include "Systems/SDLAnimatedSpriteRenderSystem.h"
#include "Systems/BoundingBoxDebugSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto manager = ManagersProvider::Instance().GetSystemsManager();

        manager->RegisterSystem<SDLInputSystem>();
        manager->RegisterSystem<MovementSystem>();
        manager->RegisterSystem<CollisionSystem>();
        manager->RegisterSystem<SDLAnimatedSpriteUpdateSystem>();
        manager->RegisterSystem<DamageSystem>();

        manager->RegisterRenderSystem<SDLTilemapSystem>();
        manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
        manager->RegisterRenderSystem<SDLAnimatedSpriteRenderSystem>();
        manager->RegisterRenderSystem<BoundingBoxDebugSystem>();
    }
}
