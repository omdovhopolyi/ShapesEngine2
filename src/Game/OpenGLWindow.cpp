#include "OpenGLWindow.h"

#include <GL/glew.h>

namespace shen
{
    bool OpenGLWindow::Init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        _window = SDL_CreateWindow
        (
            "SDL Context",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            800, 600,
            SDL_WINDOW_OPENGL
        );

        _gl_context = SDL_GL_CreateContext(_window);

        //glewExperimental = GL_TRUE;
        glewInit();

        /* The following code is for error checking. 
        *  If OpenGL has initialised properly, this should print 1.
        *  Remove it in production code.
        */
        GLuint vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        /* Error checking ends here */

        /* Freeing Memory */
        glDeleteBuffers(1, &vertex_buffer);

        return true;
    }

    void OpenGLWindow::Destroy()
    {
        SDL_GL_DeleteContext(_gl_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void OpenGLWindow::BeginFrame()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLWindow::EndFrame()
    {
        SDL_GL_SwapWindow(_window);
    }
}
