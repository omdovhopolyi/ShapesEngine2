#include "SystemsRegistration.h"
#include "SystemsManager.h"

#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"

namespace shen
{
    void RegisterSystems()
    {
        auto& manager = SystemsManager::Instance();

        manager.RegisteSystem<MovementSystem>();
        manager.RegisteSystem<RenderSystem>();
    }
}
