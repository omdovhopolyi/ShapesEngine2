#include "GLEWSystem.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(GLEWSystem)

    void GLEWSystem::Init(SystemsManager* systems)
    {
        RenderSystem::Init(systems);

        glewExperimental = GL_TRUE;
        GLenum result = glewInit();

        if (!glfwInit()) {
            bool isFail = true;
        }
        else {
            bool isOk = true;
        }
    }

    void GLEWSystem::Start()
    {

    }

    void GLEWSystem::Draw()
    {

    }
}
