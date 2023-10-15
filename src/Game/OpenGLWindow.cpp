#include "OpenGLWindow.h"
#include "Logger/Logger.h"

#include <glad/glad.h>

namespace shen
{
    bool OpenGLWindow::Init()
    {
        // TODO check errors

        const bool isOk = !SDL_Init(SDL_INIT_EVERYTHING);
        if (!isOk)
        {
            Logger::Err("Error initializing SDL");
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

        _window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            GetWidth(),
            GetHeight(),
            /*SDL_WINDOW_BORDERLESS | */SDL_WINDOW_OPENGL);

        if (!_window)
        {
            Logger::Err("Error creating SDL window");
            return false;
        }

        _glContext = SDL_GL_CreateContext(_window);

        if (!_glContext)
        {
            Logger::Err("Error creating SDL gl context: {}", SDL_GetError());
            return false;
        }

        //glewExperimental = GL_TRUE;
        //glewInit();

        gladLoadGL();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
    }

    void OpenGLWindow::Destroy()
    {
        SDL_GL_DeleteContext(_glContext);
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
