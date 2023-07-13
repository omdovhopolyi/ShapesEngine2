#include "SDLInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

#include <SDL.h>

namespace shen
{
	void SDLInputSystem::Update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<Quit>();
				break;
			}
			case SDL_KEYDOWN:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Down, event.key.keysym.sym);
				break;
			}
			case SDL_KEYUP:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Up, event.key.keysym.sym);
				break;
			}
			}
		}
	}
}
