#include "SDLInputSystem.h"

#include "Game/ManagersProvider.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Editor/EditorSystem.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

namespace shen
{
	void SDLInputSystem::Update()
	{
		auto detectMod = [](const auto eventMod)
		{
			if (eventMod & KMOD_CTRL)
			{
				return KeyMode::Crtl;
			}
			else if (eventMod & KMOD_ALT)
			{
				return KeyMode::Alt;
			}
			else if (eventMod & KMOD_SHIFT)
			{
				return KeyMode::Shift;
			}
			else
			{
				return KeyMode::None;
			}
		};

		SDL_Event event;

		auto editor = ManagersProvider::Instance().GetSystemsManager()->GetSystem<EditorSystem>();

		while (SDL_PollEvent(&event))
		{
			if (editor->IsActive())
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
			}

			switch (event.type)
			{
			case SDL_QUIT:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<Quit>();
				break;
			}
			case SDL_KEYDOWN:
			{
				auto it = _holdKeys.find(event.key.keysym.mod);
				if (it == _holdKeys.end())
				{
					auto mode = detectMod(event.key.keysym.sym);

					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Down, event.key.keysym.sym, mode);

					_scheduledFuncs.push_back([down = event.key.keysym.sym, this]()
					{
						_holdKeys.insert(down);
					});
				}
				break;
			}
			case SDL_KEYUP:
			{
				auto mode = detectMod(event.key.keysym.mod);
				_holdKeys.erase(event.key.keysym.sym);
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Up, event.key.keysym.sym, mode);
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
			ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(KeyEventType::Hold, key, KeyMode::None);
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
