#include "SDLRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Game/SDLGameWindow.h"

namespace shen
{
	void SDLRenderSystem::Start()
	{
		auto window = ManagersProvider::Instance().GetGameWindow();

		if (_window = dynamic_cast<SDLGameWindow*>(window))
		{
			_renderer = _window->GetRenderer();
		}

		// TODO asset(_renderer)
	}
}
