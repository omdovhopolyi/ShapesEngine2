#include "SDLInputSystem.h"

//#include "Game/ManagersProvider.h"
//#include "ECS/SystemsManager.h"
//#include "ECS/Systems/Editor/EditorSystem.h"
//#include "Messenger/Messenger.h"
//#include "Messenger/Events/Common.h"
//
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_sdl2.h"
//#include "imgui/imgui_impl_opengl3.h"

namespace shen
{
	//void SDLInputSystem::Update()
	//{
		/*auto detectMod = [](const auto eventMod)
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
		Uint8 justPressedMouseButton{};
		SDL_Keycode justPressedKey = SDLK_UNKNOWN;
		const auto currentMode = detectMod(SDL_GetModState());
		const auto keysArray = SDL_GetKeyboardState(NULL);

		int mouseX = 0;
		int mouseY = 0;
		const auto mouseState = SDL_GetMouseState(&mouseX, &mouseY);

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
				const bool isAlreadyPressed = keysArray[event.key.keysym.scancode];
				if (!isAlreadyPressed)
				{
					auto mode = detectMod(event.key.keysym.mod);
					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(InputEventType::Down, event.key.keysym.sym, mode);
					justPressedKey = event.key.keysym.sym;
				}

				break;
			}
			case SDL_KEYUP:
			{
				auto mode = detectMod(event.key.keysym.mod);
				ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(InputEventType::Up, event.key.keysym.sym, mode);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseMoveEvent>(
					event.motion.x,
					event.motion.y,
					event.motion.xrel,
					event.motion.yrel,
					currentMode
				);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				const bool isAlreadyPressed = (mouseState & event.button.button);
				if (!isAlreadyPressed)
				{
					justPressedMouseButton = event.button.button;

					ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
						InputEventType::Down,
						static_cast<MouseButton>(event.button.button),
						currentMode,
						event.button.x,
						event.button.y
					);
				}

				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
					InputEventType::Up,
					static_cast<MouseButton>(event.button.button),
					currentMode,
					event.button.x,
					event.button.y
				);

				break;
			}
			case SDL_MOUSEWHEEL:
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseWheelEvent>(
					event.wheel.mouseX,
					event.wheel.mouseY,
					event.wheel.y,
					currentMode
				);

				break;
			}
			}
		}

		for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			const auto isHolding = keysArray[i];
			if (isHolding)
			{
				const auto key = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i));

				if (key != SDLK_UNKNOWN && key != justPressedKey)
				{
					ManagersProvider::Instance().GetMessenger()->Broadcast<KeyEvent>(InputEventType::Hold, key, currentMode);
				}
			}
		}

		for (int i = 1; i <= sizeof(mouseState)*8; ++i)
		{
			const auto mouseButton = SDL_BUTTON(i);
			const bool isHolding = (mouseState & mouseButton);
			const bool justPressed = (mouseButton == justPressedMouseButton);
			const bool needBroadcast = (isHolding && !justPressed);

			if (needBroadcast)
			{
				ManagersProvider::Instance().GetMessenger()->Broadcast<MouseButtonEvent>(
					InputEventType::Hold,
					static_cast<MouseButton>(i),
					currentMode,
					mouseX, 
					mouseY
				);
			}
		}*/
	//}
}
