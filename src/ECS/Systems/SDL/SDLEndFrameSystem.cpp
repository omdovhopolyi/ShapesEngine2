#include <ECS/Systems/SDL/SDLEndFrameSystem.h>
#include <ECS/Systems/SDL/SDLWindowSystem.h>
#include <ECS/SystemsManager.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SDLEndFrameSystem)

    void SDLEndFrameSystem::Draw()
    {
        auto windowSystem = _systems->GetSystem<SDLWindowSystem>();
        SDL_GL_SwapWindow(windowSystem->GetWindow());
    }
}
