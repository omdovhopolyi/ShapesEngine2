#include "SystemsRegistration.h"
#include "SystemsManager.h"
#include "Game/ManagersProvider.h"

#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto manager = ManagersProvider::Instance().GetSystemsManager();

        manager->RegisteSystem<MovementSystem>();
        manager->RegisteSystem<RenderSystem>();
    }
}
