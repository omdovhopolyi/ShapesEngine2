#include "SDLInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
	void SDLInputSystem::Update()
	{
		SDL_Event event;
		SDL_Keycode down;
		bool needAddDownKey = false;

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
				auto it = _holdKeys.find(event.key.keysym.sym);
				if (it == _holdKeys.end())
				{
					down = event.key.keysym.sym;
					needAddDownKey = true;
					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Down, event.key.keysym.sym);
				}
				break;
			}
			case SDL_KEYUP:
			{
				_holdKeys.erase(event.key.keysym.sym);
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Up, event.key.keysym.sym);
				break;
			}
			}
		}

		for (const auto& key : _holdKeys)
		{
			ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Hold, key);
		}

		if (needAddDownKey)
		{
			_holdKeys.insert(down);
		}
	}
}
