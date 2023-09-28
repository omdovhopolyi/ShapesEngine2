#include "SDLInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

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
				auto it = _holdKeys.find(event.key.keysym.sym);
				if (it == _holdKeys.end())
				{
					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Down, event.key.keysym.sym);

					_scheduledFuncs.push_back([down = event.key.keysym.sym, this]()
					{
						_holdKeys.insert(down);
					});
				}
				break;
			}
			case SDL_KEYUP:
			{
				_holdKeys.erase(event.key.keysym.sym);
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Up, event.key.keysym.sym);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseMoveEvent>(
					event.motion.x,
					event.motion.y,
					event.motion.xrel,
					event.motion.yrel
				);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				auto it = _holdMouseButtons.find(event.button.button);
				if (it == _holdMouseButtons.end())
				{
					ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
						KeyEventType::Down,
						static_cast<MouseButton>(event.button.button),
						event.button.x,
						event.button.y
					);

					_scheduledFuncs.push_back([btnIndex = event.button.button, this]()
					{
						_holdMouseButtons.insert(btnIndex);
					});
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				_holdMouseButtons.erase(event.button.button);

				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
					KeyEventType::Up,
					static_cast<MouseButton>(event.button.button),
					event.button.x,
					event.button.y
				);

				break;
			}
			}
		}

		for (const auto& key : _holdKeys)
		{
			ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Hold, key);
		}

		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);

		for (const auto& mouseBtnIndex : _holdMouseButtons)
		{
			ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
				KeyEventType::Hold,
				static_cast<MouseButton>(mouseBtnIndex),
				mouseX, 
				mouseY
			);
		}

		for (const auto& func : _scheduledFuncs)
		{
			func();
		}

		_scheduledFuncs.clear();
	}
}
