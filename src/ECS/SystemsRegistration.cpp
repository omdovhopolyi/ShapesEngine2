#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/SDLTilemapSystem.h"
#include "Systems/DamageSystem.h"

#include "Systems/SDLSpriteRenderSystem.h"
#include "Systems/SDLAnimatedSpriteUpdateSystem.h"
#include "Systems/SDLAnimatedSpriteRenderSystem.h"
#include "Systems/BoundingBoxDebugSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto manager = ManagersProvider::Instance().GetSystemsManager();

        manager->RegisteSystem<MovementSystem>();
        manager->RegisteSystem<CollisionSystem>();
        manager->RegisteSystem<SDLAnimatedSpriteUpdateSystem>();
        manager->RegisteSystem<DamageSystem>();

        manager->RegisterRenderSystem<SDLTilemapSystem>();
        manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
        manager->RegisterRenderSystem<SDLAnimatedSpriteRenderSystem>();
        manager->RegisterRenderSystem<BoundingBoxDebugSystem>();
    }
}
