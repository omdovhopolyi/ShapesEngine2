#include <ECS/Systems/SDL/SDLBeginFrameSystem.h>
#include <glad/glad.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SDLBeginFrameSystem)

    void SDLBeginFrameSystem::Draw()
    {
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
