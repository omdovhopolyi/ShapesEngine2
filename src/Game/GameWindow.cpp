#include "GameWindow.h"
#include "Logger/Logger.h"

namespace shen
{
    bool GameWindow::Init()
    {
		const int result = SDL_Init(SDL_INIT_EVERYTHING);
		if (result != 0)
		{
			Logger::Err("Initializing SDL");
			return false;
		}

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		_winWidth = displayMode.w;
		_winHeight = displayMode.h;

		_window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_winWidth,
			_winHeight,
			SDL_WINDOW_BORDERLESS);

		if (!_window)
		{
			Logger::Err("Error creating window");
			return false;
		}

		_renderer = SDL_CreateRenderer(_window, -1, 0);
		if (!_renderer)
		{
			Logger::Err("Error creating renderer");
			return false;
		}

		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

		return true;
    }

    void GameWindow::Destroy()
    {
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
    }
}
