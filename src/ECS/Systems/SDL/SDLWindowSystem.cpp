#include <ECS/Systems/SDL/SDLWindowSystem.h>
#include <Logger/Logger.h>

#include <Serialization/WrapperTypes/XmlDataElementWrapper.h>
#include <Utils/FilePath.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SDLWindowSystem)

    void SDLWindowSystem::Start()
    {
        CreateSDLWindow();
    }

    void SDLWindowSystem::Stop()
    {
        if (_window) {
            SDL_DestroyWindow(_window);
        }
    }

    SDL_Window* SDLWindowSystem::GetWindow() const
    {
        return _window;
    }

    unsigned int SDLWindowSystem::GetWindowFlags() const
    {
        return 0;
    }

    //sf::Vector2i SDLWindowSystem::GetSize();

    void SDLWindowSystem::Load()
    {
        auto elementWrapper = XmlDataElementWrapper{ GetSystems() };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/window.xml"));
        //_size = elementWrapper.GetIntVec2("size", sf::Vector2i(800, 640));
        _name = elementWrapper.GetStr("name");
        _titlebar = elementWrapper.GetBool("titlebar", true);
        _resize = elementWrapper.GetBool("resize", true);
        _close = elementWrapper.GetBool("close", true);
        _fullscreen = elementWrapper.GetBool("fullscreen", false);
    }

    void SDLWindowSystem::CreateSDLWindow()
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _window = SDL_CreateWindow(
            _name.c_str(),
            1280,
            720,
            SDL_WINDOW_OPENGL
        );

        if (!_window) {
            Logger::Err("Failed to create SDL window");
            return;
        }

        SDL_GLContext context = SDL_GL_CreateContext(_window);
        if (!context) {
            Logger::Err("Failed to create GL context");
            return;
        }

        SDL_GL_MakeCurrent(_window, context);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            Logger::Err("GLAD init failed");
        }
    }
}
