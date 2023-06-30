#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/SDLTilemapSystem.h"
#include "Systems/SDLSpriteRenderSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto manager = ManagersProvider::Instance().GetSystemsManager();

        manager->RegisteSystem<MovementSystem>();

        manager->RegisterRenderSystem<SDLTilemapSystem>();
        manager->RegisterRenderSystem<SDLSpriteRenderSystem>();
    }
}
